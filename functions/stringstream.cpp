#include<iostream>
#include<sstream>

int main() {
        std::istringstream iss("test 123 123hah ahha");
        std::string str, str1, str2;
        int inta;

        std::cout<< iss.str() <<std::endl;
        iss >> str >> str1 >> str2 >> inta;
        std::cout<<"str  : "<< str  <<std::endl;
        std::cout<<"str1 : "<< str1 <<std::endl;
        std::cout<<"str2 : "<< str2 <<std::endl;
        std::cout<<"inta : "<< inta <<std::endl;

}

// #include<iostream>
// #include<sstream>

// int main() {
//         std::ostringstream oss;
//         int inta = 10;
//         std::string str = " test_string";
//         oss << "test " << inta << str <<std::endl;
//         std::cout<< oss.str();
// }