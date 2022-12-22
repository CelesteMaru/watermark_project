#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
using namespace cv;
using namespace std;

class ImageEditor{
    public:
        ImageEditor();
        bool ImageEditor::writeTextOnImage(std::string pathIn);
        bool ImageEditor::writeTextOnImage(std::string pathIn, std::string pathOut);

        void ImageEditor::setWatermarkText(std::string text);
        void ImageEditor::setFontSize(float fontSize, bool isProportionate);
        void ImageEditor::setOutputFolder(std::string outputFolder);

        bool ImageEditor::setVerticalAlignment(std::string alignment);
        bool ImageEditor::setHorizontalAlignment(std::string alignment);
    private :
        std::string watermarkText;
        std::string outputFolder;

        int verticalAlignment = 3;
        int horizontalAlignment = 3;

        float fontSize = 1.f;
        bool isFontSizeProportionate = false;
        
};