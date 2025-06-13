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

const char * data = R"(vpmkpp [operation] ...
operation:
build               Build the doc.
key                 Set the key to decrypt respective keys in a program(Use carefully).
docpath             Set the input doc path
outpath             Set the output markdowns path
)";

//this is not suggested
std::string key = "",docp = "",outp = "";
std::string config_path = "";

int BuildDocs(const std::string & docp,const std::string& outp);

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
        if(!docp.compare(""))std::cout << "Currently(leave blank to keep):" << docp << std::endl;
        std::string result;
        getline(std::cin,result);
        if(result.compare(""))docp = result;
        return 0;
    }else if(!std::strcmp(argv[1],"outpath")){
        if(!outp.compare(""))std::cout << "Currently(leave blank to keep):" << outp << std::endl;
        std::string result;
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
    std::cout << "\n[DocPath]" << docp << "\n[OutPath]" << outp << std::endl;

    if(!std::strcmp(argv[1],"build")){
      std::cout << "Starting to build the docs...\n";
      int ret = BuildDocs(docp_exe,outp_exe);
      if(!ret){
        std::cout << "Successfully build the program!" << std::endl;
      }else std::cerr << "Failed to build the program.Error code:" << ret << std::endl;
    }

    return 0;
}

int BuildDocs(const std::string& dp,const std::string& op){
    //step0: read doc config: like keys ...
    //step1: recursively get all the markdown files...
    //step2: transform markdown to what we needed
    //step3: copy newly added resources
    return 0;
}
