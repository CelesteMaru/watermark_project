#include "src/ImageEditor.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <regex>
#include <filesystem>
namespace win32{
#include <windows.h>
//#include <ShlObj.h>
}


using namespace win32;

int main(int argc, char *argv[]) {
   bool fileSelector = false;
   bool dirError;
   std::string dirpath;
   std::string outputFolder;
   std::string argument;
   std::string textToWrite = "Pierre Maruejol";
   std::regex fileRegex(".*(.png)$");
   std::regex folderRegex("^[a-zA-Z]:(\\\\|\\/)(?:(\\w|\\s|\\d)+(\\\\|\\/)?)*$");
   std::regex floatRegex("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
   ImageEditor imageEditor;
   
   

   // option manager
   for (size_t i = 1; i < argc; i++)
   { 
      argument=argv[i];

      //---------------------------------- Help -----------------------------------//
      if(argument=="-h" || argument=="-help" || argc==1){
         cout << "This project is meant to facilitate the action of puting a watermark on drawings and created images \n\n"
         << " -h | -help displays the list of option and what they are used for \n"
         // TO-DO : << " -help-command |-hc displays a specific option explanation with an example \n"
         << " -f uses the fileselector NOTE it is a file selector not a directory selector \n"
         << " -d [path/to/directory] puts the watermarks to every images in the directory \n"
         << " -o [path/to/directory] sets the output directory (by default it is the same directory as the input) \n" 
         << " -t [text_to_watermark] sets the text that will be written as a watermark (by default it is Pierre Maruejol) \n"
         << " -fontSize | -fs [size] sets the font size to a specific value (by default is is set to the minimum: 1). You can also make it proportionnal to the width if you add a % after the number \n"
         << " -verticalAlign | -vAlign [top/above/middle/below/bottom] sets the vertical align to the according position (by default middle) \n"
         << " -horizontalAlign | -hAlign [left/leftward/middle/rightward/right] sets the horizontal align to the according position (by default middle) \n"
         << "\n" ;  

      }

      //----------------------------- File Selector -------------------------------//
      else if (argument=="-f"){
         fileSelector=true;
      } 

      //----------------------------- Input Directory -----------------------------//
      else if (argument=="-d"){
         if(i+1<=argc){
            i++;
            dirpath=argv[i];
             if(regex_match(dirpath, folderRegex)){
               // cleaning up the path if the last folder is not followed by a \ 
               if(dirpath.back()!='\\'){
                  dirpath.append("\\");
               }            
               // if directory at dirpath doesn't exist 
               struct stat buffer;   
               if(stat (dirpath.c_str(), &buffer) != 0){
                  dirpath= "";
                  std::cerr << "The path " << dirpath << " doesn't lead to a directory \n" ;
               } 
            }
            else{
               std::cerr << "The path " << dirpath << " isn't a valid path \n";
            }
         }
         else{
            std::cerr << "You must provide the path to the directory after the option "<< argument << "\n";
         }
      }

      //----------------------------- Output Directory -----------------------------//
      else if (argument=="-o"){
         if(i+1<=argc){
            i++;
            
            outputFolder=argv[i];

            if(regex_match(outputFolder, folderRegex)){
               imageEditor.setOutputFolder(outputFolder);
               std::filesystem::create_directories(outputFolder);
            }
            else{
               std::cerr << "The path " << outputFolder << " isn't a valid path \n";
            }
         }
         else{
            std::cerr << "You must provide the path to the directory after the option "<< argument <<" \n";
         }
      }
      
      //----------------------------- Text setter -----------------------------//
      else if (argument=="-t"){
         if(i+1<=argc){
            i++;
            
            textToWrite=argv[i];
         }
         else{
            std::cerr << "You must provide the text to watermark after the option "<< argument << " \n";
         }
      }

      //----------------------------- Font Size ----------------------------------//
      else if(argument=="-fs"||argument=="-fontSize"){
         if(i+1<=argc){
            i++;
            
            std::string fontSize=argv[i];

            bool isProportionate = (fontSize.back() == '%');
            if(isProportionate){
               fontSize.pop_back();
            }
            if(regex_match(fontSize, floatRegex)){
               imageEditor.setFontSize(std::stof(fontSize), isProportionate);
            }
            else{
               std::cerr << "The font size " << fontSize << " is not a valid font size plase input a number followed or not by % (e.g. 1.50% )\n";
            }
         }
         else{
            std::cerr << "You must provide a fontsize after the option " << argument << " \n";
         }
      }

      //----------------------------- Vertical Align -----------------------------//
      else if (argument=="-verticalAlign"||argument=="-vAlign"){
         if(i+1<=argc){
            i++;
            
            std::string alignment=argv[i];

            bool check = imageEditor.setVerticalAlignment(alignment);
            if(!check){
               std::cerr << "The alignment " << alignment << " is not a valid alignment please use one of the following : [top/above/middle/below/bottom] \n";
            }
         }
         else{
            std::cerr << "You must provide a vertical alignment after the option " << argument << " \n";
         }
      }

      //----------------------------- Horizontal Align -----------------------------//
      else if (argument=="-horizontalAlign"||argument=="-hAlign"){
         if(i+1<=argc){
            i++;
            
            std::string alignment=argv[i];

            bool check = imageEditor.setHorizontalAlignment(alignment);
            if(!check){
               std::cerr << "The alignment " << alignment << " is not a valid alignment please use one of the following : [left/leftward/middle/rightward/right] \n";
            }
         }
         else{
            std::cerr << "You must provide a horizontal alignment after the option "<< argument << " \n";
         }
      }

      //---------------------------------- Else -----------------------------------//
      else{
         std::cout << "Option \"" << argument << "\" doesn't exist please use the -h option to know which option is available \n";
      }
      
   }

   imageEditor.setWatermarkText(textToWrite);
   

   // -d 
   if(!std::equal(dirpath.begin(), dirpath.end(), "")){
      for (const auto & file : std::filesystem::directory_iterator(dirpath)){
         std::string fileName = file.path().string();
         if(regex_match(fileName, fileRegex)){
            imageEditor.writeTextOnImage(fileName);
         }
      }  
   }

   
   // -f
   if(fileSelector){
      win32::OPENFILENAME ofn;
      ZeroMemory( &ofn,  sizeof( ofn ) );
      ofn.lStructSize  = sizeof( ofn );
      ofn.lpstrFilter  = (win32::LPCSTR) "PNG files" "\0"  "*.png" "\0" 
                     "Any File"   "\0"  "*.*"   "\0";
      ofn.nFilterIndex = 1;
      ofn.lpstrFile    = (win32::LPSTR)dirpath.c_str();
      ofn.nMaxFile     = MAX_PATH;
      ofn.Flags        = OFN_CREATEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
   
      if (!win32::GetOpenFileName ((win32::LPOPENFILENAME)&ofn)){
         std::cerr << ofn.lpstrFile << " is not a file";
      }
      else{
         bool check = imageEditor.writeTextOnImage((char*)ofn.lpstrFile );
         // if error while writing the image
         if (check == false) {
            cerr << "Mission - Saving the image, FAILED \n";
      
            // wait for any key to be pressed
            cin.get();
         }
      }
  }
  
   return 0;
}