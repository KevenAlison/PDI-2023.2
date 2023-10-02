#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, image_sborda, image_fill, image_original;
  int width, height, n_objects, n_objremovido;

  Point p;
  image = imread(argv[1], IMREAD_GRAYSCALE);
  image_original = image.clone();
  if(!image.data){
    cout << "Erro ao abrir a imagem";
    return(-1);
  }

  width=image.cols;
  height=image.rows;
  cout << width << "x" << height << endl;

  p.x=0;
  p.y=0;
  n_objremovido = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255 && (i == 0 || i == height-1 || j == 0 || j == width-1)){
        n_objremovido++;
        p.x=j;
        p.y=i;
        floodFill(image,p,0);
      }
    }
  }
  image_sborda = image.clone();

  n_objects = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        n_objects++;
        n_objremovido++;
        p.x=j;
        p.y=i;
  	// preenche o objeto com o contador
	floodFill(image,p,n_objects);
      }
    }
  }
  p.x=0;
  p.y=0;
  floodFill(image,p,255);

  int buracos=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0){
        buracos++;
        p.x=j;
        p.y=i;
		  floodFill(image,p,buracos);
      }
    }
  }
  cout << "Nº total de objetos: " << n_objects << endl;
  cout << "Nº bolhas sem buracos: " << n_objects - buracos << endl;
  cout << "Nº bolhas com buracos: " << buracos << endl;
  equalizeHist(image, image_fill);
  imshow("Imagem Original", image_original);
  imshow("Imagem s/ bolha borda", image_sborda);
  imwrite("Imagem s/ bolha borda.png",image_sborda);
  imshow("Bolhas preenchidas", image_fill);
  imwrite("labeling.png", image);
  waitKey();

  return 0;
}
