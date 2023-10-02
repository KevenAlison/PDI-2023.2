#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat img_encoded, img_decoded;
    Vec3b val_encoded, val_decoded;
    int nbits = 3;

    img_encoded = imread(argv[1], IMREAD_COLOR);

    if (img_encoded.empty()) {
        cout << "Erro ao abrir a imagem" << endl;
        return -1;
    }

    img_decoded = img_encoded.clone();

    for (int i = 0; i < img_encoded.rows; i++) {
        for (int j = 0; j < img_encoded.cols; j++) {
            val_encoded = img_encoded.at<Vec3b>(i, j);

            val_decoded[0] = val_encoded[0] << (8-nbits);
            val_decoded[1] = val_encoded[1] << (8-nbits);
            val_decoded[2] = val_encoded[2] << (8-nbits);

            img_decoded.at<Vec3b>(i, j) = val_decoded;
        }
    }
    imshow("Imagem Codificada", img_encoded);
    imshow("Imagem Decodificada", img_decoded);
    imwrite("imagem_decodificada.png",img_decoded);
    waitKey();

    return 0;
}
