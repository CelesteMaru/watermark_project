#include "ImageEditor.h"


ImageEditor::ImageEditor(){
}


bool ImageEditor::writeTextOnImage(std::string path){
    int lastSlashPosition = 0;
    int lastDotPosition = 0;
    int iterator = 0;
    for (char c : path){
        if(c=='/' || c=='\\'){
            lastSlashPosition=iterator;

        }else if (c=='.')
        {
            lastDotPosition=iterator;
        }
        iterator++;
    }
    std::string pathToFolder;
    if (std::equal(outputFolder.begin(), outputFolder.end(), "")){
        pathToFolder = path.substr(0, lastSlashPosition+1); // From 0 to lastSlash
    }
    else {
        pathToFolder=outputFolder;
    }
    
    std::string filename = path.substr(lastSlashPosition+1, lastDotPosition-lastSlashPosition-1); //From last slash with the length lastDot - lastSlash
    std::string fileExtension = path.substr(lastDotPosition);

    return writeTextOnImage(path, pathToFolder+filename+"_watermarked"+fileExtension);
}

bool ImageEditor::writeTextOnImage( std::string path, std::string pathOut){
    Mat image = imread(path, IMREAD_ANYCOLOR);
    Mat textLayer;
    image.copyTo(textLayer);
    double alpha = 0.3;

    int width= image.size[0];
    int height = image.size[1];
    float imgFontSize;

    //Declaring the font size//
    if (isFontSizeProportionate){
        imgFontSize = std::max(((fontSize / 13333333) * width), 1.f);

    }
    else{
        imgFontSize = std::max(fontSize, 1.f);
    }
    
    Scalar fontColorB(0, 0, 0); //Declaring the color of the border of the text//
    Scalar fontColorW(255, 255, 255); //Declaring the color of the text//
    int fontWeight = 2; //Declaring the font weight//
    int fontFace = FONT_HERSHEY_COMPLEX;


    Point alignedPosition(width* 0.25 *(verticalAlignment-1), height * 0.25 *(horizontalAlignment-1));// Declaring the text position //

    Size textSize = getTextSize(watermarkText, fontFace, imgFontSize, fontWeight, nullptr);
    
    Point textPosition(alignedPosition.y-textSize.width* 0.25 *(horizontalAlignment-1),
    alignedPosition.x-textSize.height * 0.5 *(verticalAlignment-3));
    
    putText(textLayer, watermarkText, textPosition ,fontFace, imgFontSize, fontColorW, fontWeight+1); //Putting a fontColorW border to the text in the matrix//
    putText(textLayer, watermarkText, textPosition ,fontFace, imgFontSize, fontColorB, fontWeight); //Putting the text in the matrix//
    
    addWeighted(textLayer, alpha, image, 1-alpha, 0, image);
    
    bool check = imwrite(pathOut, image);
  
    // if the image is not saved
    return check;
}

void ImageEditor::setWatermarkText(std::string text){
    watermarkText=text;
}

void ImageEditor::setFontSize(float fontSize, bool isProportionate){
    this->fontSize=fontSize;
    this->isFontSizeProportionate=isProportionate;
}

void ImageEditor::setOutputFolder(std::string path){
    outputFolder=path;
}

bool ImageEditor::setVerticalAlignment(std::string alignment){
    if(alignment=="top"){
        verticalAlignment=1;
    }
    else if(alignment=="above"){
        verticalAlignment=2;
    }
    else if(alignment=="middle"){
        verticalAlignment=3;
    }
    else if(alignment=="below"){
        verticalAlignment=4;
    }
    else if(alignment=="bottom"){
        verticalAlignment=5;
    }
    else{
        return false;
    }
    return true;
}

bool ImageEditor::setHorizontalAlignment(std::string alignment){
    if(alignment=="right"){
        horizontalAlignment=5;
    }
    else if(alignment=="rightward"){
        horizontalAlignment=4;
    }
    else if(alignment=="middle"){
        horizontalAlignment=3;
    }
    else if(alignment=="leftward"){
        horizontalAlignment=2;
    }
    else if(alignment=="left"){
        horizontalAlignment=1;
    }
    else{
        return false;
    }
    return true;
}