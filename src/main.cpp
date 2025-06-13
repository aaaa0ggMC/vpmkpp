/** @file main.cpp
* @brief a simple markdown processor,single file
* @par Requirements:
* C++ 23
* Crypto++
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <ranges>
#include <unordered_map>
#include <memory>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

const char * data = R"(vpmkpp [operation] ...
operation:
build               Build the doc.
key                 Set the key to decrypt respective keys in a program(Use carefully).
docpath             Set the input doc path
outpath             Set the output markdowns path
addDocKey           Add a new key to the doc
)";

//this is not suggested
std::string key = "",docp = "",outp = "";
std::string config_path = "";
std::vector<CryptoPP::byte> kb;

int BuildDocs(const std::string & docp,const std::string& outp);
void readDocKeys(const std::string& dp,std::unordered_map<std::string,std::shared_ptr<CryptoPP::byte>>& keys);
std::string hex8_str(const std::string& hex8);
std::vector<uint8_t> str_byte(const std::string& str);
std::vector<uint8_t> hex8_byte(const std::string& hex); 
template<class T,class... Vs> void align(std::vector<T> & vec,size_t size,bool canRemoveEle,Vs&&... args);

int main(int argc,char * argv[]){
    if(argc < 2){
        std::cout << data << std::endl;
        return -1;
    }
    //read essentila data
    std::system("mkdir -p $HOME/.local/share/vpmkpp");
    {
      char * data = std::getenv("HOME");
      if(data)config_path = data;
      else config_path = "";
    }
    config_path += "/.local/share/vpmkpp/config";

    std::ifstream ifs(config_path);


    if(!ifs.good()){
        std::cout << "Error occurred when loading the config file." << std::endl;
    }else{
        //See AlwaysLearning/C.Cpp/Tests/test0: No Except will happen
        std::getline(ifs,key);
        std::getline(ifs,docp);
        std::getline(ifs,outp);
        ifs.close();
    }

    atexit([]{
      std::ofstream ofs(config_path);
      if(ofs.good()){
        ofs << key << "\n" << docp << "\n" << outp << "\n";
        ofs.close();
      }
    });

    if(!std::strcmp(argv[1],"key")){
      //set key
      if(key.compare("")){
        std::cout << "Warning: The origin key is not blank,it may break other docs!!"
            "\nLeave blank to keep it!" << std::endl;
      }
      std::string result = "";
      std::cout << "Note that the key is stored in the local computer in origin form,so do not choose your frequently used password.\nKey:";
      getline(std::cin,result);
      if(result.compare(""))key = result;
      return 0;
    }else if(!std::strcmp(argv[1],"docpath")){
        if(docp.compare(""))std::cout << "Currently(leave blank to keep):" << docp << std::endl;
        std::string result;
        std::cout << "DocPath:";
        getline(std::cin,result);
        if(result.compare(""))docp = result;
        return 0;
    }else if(!std::strcmp(argv[1],"outpath")){
        if(outp.compare(""))std::cout << "Currently(leave blank to keep):" << outp << std::endl;
        std::string result;
        std::cout << "OutPath:";
        getline(std::cin,result);
        if(result.compare(""))outp = result;
        return 0;
    }

    if(!key.compare("")){
        std::cerr << "Error: Key is empty!Please use \"vpmkpp key\" to set the encrypt key!" << std::endl;
        return -1;
    }

    std::string docp_exe = "",outp_exe = "";

    if(!docp.compare("")){
        std::cerr << "Warning: DocPath is empty!You can use \"vpmkpp docpath\" to avoid this warning." << std::endl;
        std::cout << "Now enter the docpath:";
        std::string result = "";
        std::getline(std::cin,result);
        if(!result.compare("")){
          std::cerr << "Error: Invalid path!!" << std::endl;
          return -1;
        }
        docp_exe = result;
    }else docp_exe = docp;

    if(!outp.compare("")){
        std::cerr << "Warning: OutPath is empty!You can use \"vpmkpp outpath\" to avoid this warning." << std::endl;
        std::cout << "Now enter the outpath:";
        std::string result = "";
        std::getline(std::cin,result);
        if(!result.compare("")){
          std::cerr << "Error: Invalid path!!" << std::endl;
          return -1;
        }
        outp_exe = result;
    }else outp_exe = outp;

    std::cout << "----------Config-------" << std::endl;
    std::cout << "[Key(Sensitive)]";
    std::ranges::copy(key | std::views::enumerate | std::views::transform([](auto pair){
      auto [index,ch] = pair;
      if(key.size() <= 6 || (index > 2 && index < key.size()-2))return '*';
      return ch;
    }),std::ostream_iterator<char>(std::cout));
    std::cout << "\n[DocPath]" << docp_exe << "\n[OutPath]" << outp_exe << std::endl;

    //Gen kb
    align(kb,CryptoPP::AES_DEFAULT_KEYLENGTH,true,0);

    if(!std::strcmp(argv[1],"build")){
      std::cout << "Starting to build the docs...\n";
      int ret = BuildDocs(docp_exe,outp_exe);
      if(!ret){
        std::cout << "Successfully build the program!" << std::endl;
      }else std::cerr << "Failed to build the program.Error code:" << ret << std::endl;
    }else if(!std::strcmp(argv[1],"addDocKey")){
      std::string name,dockey;
      std::cout << "Name:";
      std::cin >> name;
      std::getline(std::cin,dockey);
      std::cout << "DocKey:";
      std::getline(std::cin,dockey);
      
      if(!dockey.compare("") || !name.compare("")){
        std::cerr << "Error:value shouldn't be empty!" << std::endl;
        return -1;
      }

      ///Encrypt
      using namespace CryptoPP;
      CFB_Mode<AES>::Encryption enc;
      auto kdocb = str_byte(dockey);
      byte iv[AES::BLOCKSIZE];
      AutoSeededRandomPool prng;
      prng.GenerateBlock(iv,sizeof(iv));
      enc.SetKeyWithIV(&kb[0],kb.size(),iv,sizeof(iv));
      std::vector<uint8_t> bytes_data;
      ArraySource(kdocb.data(),kdocb.size(),true,new StreamTransformationFilter(enc,new VectorSink(bytes_data)));
      std::cout << "Result:";
      for(auto data : bytes_data){
        std::cout << data << " ";
      }
    }else{
      std::cerr << "Error:Unknown command!" << std::endl;
    }

    return 0;
}

int BuildDocs(const std::string& dp,const std::string& op){
    //step0: read doc config: like keys ...
    std::unordered_map<std::string,std::shared_ptr<CryptoPP::byte>> keys;
    readDocKeys(dp,keys);
    //step1: recursively get all the markdown files...
    //step2: transform markdown to what we needed
    //step3: copy newly added resources
    return 0;
}

void readDocKeys(const std::string& dp,std::unordered_map<std::string,std::shared_ptr<CryptoPP::byte>>& map_keys){
  using namespace CryptoPP;
  std::string path = (dp[dp.size()-1] == '/')?dp:(dp + "/");
    std::ifstream keys(path + "vpmkpp.keys");
    if(keys.good()){
     std::string k,v,iv;
     while(!keys.eof()){
        keys >> k;
        keys >> v;//hex8 iv(16b) & key
        keys >> iv;//iv used to encrypt the key,hex8 enced

        //Decrypt
        CFB_Mode<AES>::Decryption dec;
        auto ivb = hex8_byte(iv);
        auto vhex = hex8_byte(v);
        std::vector<uint8_t> result = {};
        dec.SetKeyWithIV(&kb[0],kb.size(),&ivb[0]);
        ArraySource(vhex.data(),vhex.size(),true,new StreamTransformationFilter(dec,new VectorSink(result)));
        std::cout << "Read key:" << std::string(result.begin() + 16,result.end()) << std::endl; 
     }
    }else std::cout << "No doc keys detected" << std::endl;
}

std::string hex8_str(const std::string& hex) {
    if (hex.length() % 2 != 0) {
        return "";
    }

    std::string decoded;
    CryptoPP::HexDecoder decoder;
    decoder.Attach(new CryptoPP::StringSink(decoded));
    
    try {
        decoder.Put(reinterpret_cast<const CryptoPP::byte*>(hex.data()), hex.size());
        decoder.MessageEnd();
    } catch (const CryptoPP::Exception& e) {
        return "";
    } 
    return decoded;
}

std::vector<uint8_t> hex8_byte(const std::string& hex) {
    std::string decoded;
    CryptoPP::StringSource ss(&hex[0], true,
        new CryptoPP::HexDecoder(
            new CryptoPP::StringSink(decoded)
        )
    );
    return std::vector<uint8_t>(decoded.begin(), decoded.end());
}

std::vector<uint8_t> str_byte(const std::string& str) {
    return std::vector<uint8_t>(str.begin(), str.end());
}

template<class T,class... Vs> void align(std::vector<T> & vec,size_t size,bool canRemoveEle,Vs&&... args){
  size_t sz = vec.size();
  if(sz >= size){
    if(canRemoveEle){
      vec.erase(vec.begin() + (size - 1),vec.end());
    }
    return;
  }else{
    for(size_t i = sz;i < size;++i){
      vec.emplace_back(args...);
    }
  }
}
