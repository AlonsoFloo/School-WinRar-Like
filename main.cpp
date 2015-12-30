#include "winuscompressor.h"

#include <iostream>
#include <QDir>
#include <QFile>


using namespace std;

int main()
{
    int userChoose = 0;

    do {
        cout << "Menu :" << endl;
        cout << "1 - Compress" << endl;
        cout << "2 - Uncompress" << endl;
        cout << "3 - Quit" << endl;
        cin >> userChoose;

        if (userChoose != 3) {
            string ecfFile;
            int threadNumber;
            string folder;
            bool erreurInUserValues = false;
            do {
                cout << "Thread number : ";
                cin >> threadNumber;
                cout << "Folder (With final /) : ";
                cin >> folder;
                cout << "File ecf : ";
                cin >> ecfFile;
                cout << endl << endl << endl;
                erreurInUserValues = threadNumber <= 0 || ecfFile == "" || folder == "";
                if (erreurInUserValues) {
                    cout << "Merci de rentré des valeurs correctess";
                }
            } while (erreurInUserValues);

            QString filePath = QString::fromStdString(ecfFile);
            QString dirPath = QString::fromStdString(folder);
            WinUsCompressor compressor(threadNumber);
            if (userChoose == 1) {
                cout << "Compressing ..." << endl << endl << endl;
                compressor.compress(dirPath, filePath);
            } else if (userChoose == 2) {
                cout << "Un Compressing ..." << endl << endl << endl;
                compressor.uncompress(filePath, dirPath);
            }
        }

    } while (userChoose != 3);

    return 0;
}

