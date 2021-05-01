#include <iostream>
#include <fstream>

using namespace std;

// void status_write(std::ifstream &file_read, std::ofstream &file_write)
void status_write(std::ifstream file_read, std::ofstream file_write)
{
	cout << "---------" << endl;
	cout << file_read.is_open() << endl;
	cout << file_write.is_open() << endl;
	cout << "---------" << endl;
}


int main()
{
	std::ifstream input_stream("./stat");
	
	std::ifstream file_read;
	std::ofstream file_write;
	std::string filename = "yunslee";
	filename.append("_shrubbery");

	status_write(file_read, file_write);

	file_write.open(filename);
	std::cout << "Write Ascii tree, file name : " << filename << std::endl;
	std::string tree =
	"                                              .       \n \
                                        .         ;        \n \
           .              .              ;%     ;;         \n \
             ,           ,                :;%  %;          \n \
              :         ;                   :;%;'     .,   \n \
     ,.        %;     %;            ;        %;'    ,;     \n \
       ;       ;%;  %%;        ,     %;    ;%;    ,%'      \n \
        %;       %;%;      ,  ;       %;  ;%;   ,%;'       \n \
         ;%;      %;        ;%;        % ;%;  ,%;'         \n \
          `%;.     ;%;     %;'         `;%%;.%;'           \n \
           `:;%.    ;%%. %@;        %; ;@%;%'              \n \
              `:%;.  :;bd%;          %;@%;'                \n \
                `@%:.  :;%.         ;@@%;'                 \n \
                  `@%.  `;@%.      ;@@%;                   \n \
                    `@%%. `@%%    ;@@%;                    \n \
                      ;@%. :@%%  %@@%;                     \n \
                        %@bd%%%bd%%:;                      \n \
                          #@%%%%%:;;                       \n \
                          %@@%%%::;                        \n \
                          %@@@%(o);  . '                   \n \
                          %@@@o%;:(.,'                     \n \
                      `.. %@@@o%::;                        \n \
                         `)@@@o%::;                        \n \
                          %@@(o)::;                        \n \
                         .%@@@@%::;                        \n \
                         ;%@@@@%::;.                       \n \
                        ;%@@@@%%:;;;.                      \n \
                    ...;%@@@@@%%:;;;;,..                   \n";
		file_write.write(tree.c_str(), tree.size());
		file_write.close();

	return (1);
}

