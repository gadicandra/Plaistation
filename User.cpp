#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <limits>
#include "UI.h"
#include "User.h"
using namespace std;

bool User::regist(){ //Untuk melakukan registrasi
    header();
    cout << "Masukkan username(tanpa spasi): " << endl;
    cin >> username;

    //Melakukan pengecekkan apakah username telah terdaftarkan
    ifstream myfile("account.txt");
    string line;

    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(username == line){
                cout << "Username telah digunakan" << endl;
                myfile.close();
                return false;
            }
        }
    }

    cout << "Masukkan password(tanpa spasi): " << endl;
    cin >> password;
    cout << "Masukkan ulang password(tanpa spasi):" << endl;
    cin >> rePassword;

    //Melakukan pengecekan apakah password dengan password perulangan sama
    if(password == rePassword){
        isCorrect = true;
    } else {
        cout << "Password berbeda masukkan ulang!" << endl;
        isCorrect = false;
    }
    return isCorrect;
}

bool User::loginAsMember(){ //Untuk melakukan login dan pengecekan memiliki akun atau tidak
    header();
    int currentLine = 1;
    checkUsername = "-1";
    isCorrect = false;

    cout << "Masukkan username(tanpa spasi): " << endl;
    cin >> username;
    cout << "Masukkan password(tanpa spasi): " << endl;
    cin >> password;

    //Melakukan pengecekan apakah username dan password benar
    ifstream myfile("account.txt");
    string line;

    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(username == line){
                targetLine = currentLine;
                checkUsername = line;
            } else if (currentLine == targetLine + 1){
                checkPassword = line;
                break;
            }
            currentLine++;
        }
        myfile.close();
    } else {
        myfile.close();
    }

    while(!isCorrect){
        if(password == checkPassword){
            isCorrect = true;
            cout << "Login Berhasil";
            return true;
        } else if (checkUsername != "-1" && password != checkPassword){
            header();
            cout << "Password salah, masukkan lagi: " << endl;
            cin >> password;
            continue;
        } else if (checkUsername != "-1"){
            header();
            cout << "Akun tidak ditemukan, silahkan register" << endl;
            return false;
        }
    }
   return 0;
}

bool User::loginAsAdministrator(){
    header();
    int currentLine = 1;
    checkUsername;
    isCorrect = false;

    cout << "Masukkan username(tanpa spasi): " << endl;
    cin >> username;
    cout << "Masukkan password(tanpa spasi): " << endl;
    cin >> password;

    //Melakukan pengecekan apakah username dan password benar
    ifstream myfile("accountAdministrator.txt");
    string line;

    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(username == line){
                targetLine = currentLine;
                checkUsername = line;
            } else if (currentLine == targetLine + 1){
                checkPassword = line;
                break;
            }
            currentLine++;
        }
        myfile.close();
    } else {
        myfile.close();
    }

    while(!isCorrect){
        if(password == checkPassword){
            isCorrect = true;
            cout << "Login Berhasil";
            return true;
        } else {
            header();
            cout << "Password salah, masukkan lagi: " << endl;
            cin >> password;
            continue;
        }
    }
    return 0;
}

int User::profil(string us){
    header();
    int currentLine = 1;
    ifstream myfile("account.txt");
    string line;
        
    if(myfile.is_open()){
        while(getline(myfile, line)){
            if(us == line){
                targetLine = currentLine;
            } else if (currentLine == targetLine + 2){
                nama = line;
            } else if (currentLine == targetLine + 3){
                email = line;
            } else if (currentLine == targetLine + 4){
                noTelp = line;
            } else if (currentLine == targetLine + 5){
                idNumber = line;
                break;
            }
            currentLine++;
        }
        myfile.close();
    }

    cout << "Nama    : " << nama  << endl;
    cout << "Email   : " << email << endl;
    cout << "No. Telp: " << noTelp << endl;
    cout << "NIK     : " << idNumber << endl;
    cout << "========================================" << endl;
    return menuProfil();
}

void User::updateData(string us){
    header();
    cout << "Masukkan Nama: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,nama);
    cout << "Masukkan Email: " << endl;
    cin >> email;
    cout << "Masukkan No Telepon: " << endl;
    cin >> noTelp;
    cout << "Masukkan NIK: " << endl;
    cin >> idNumber;
    replaceLine(us);
}

void User::replaceLine(string us){
    fstream file("account.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    string line;
    int currentLine = 1;
    while(getline(file, line)){
        if(us == line){
            targetLine = currentLine;
            tempFile << us << endl;
        } else if (currentLine == targetLine + 2){
            tempFile << nama << endl;
        } else if (currentLine == targetLine + 3){
            tempFile << email << endl;
        } else if (currentLine == targetLine + 4){
            tempFile << noTelp << endl;
        } else if (currentLine == targetLine + 5){
            tempFile << idNumber << endl;
        } else {
            tempFile << line << endl;
        }
        currentLine++;
    }

    file.close();
    tempFile.close();

    // Hapus file asli
    if (remove("account.txt") != 0) {
        cout << "Gagal menghapus file asli." << endl;
        return;
    }

    // Ganti nama file sementara menjadi nama file asli
    if (rename("temp.txt", "account.txt") != 0) {
        cout << "Gagal mengganti nama file." << endl;
        return;
    }
}

void User::Delete(string us){
    fstream file("account.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    string line;
    int currentLine = 1;
    while(getline(file, line)){
        if(us == line){
            targetLine = currentLine;
        } else if(currentLine == targetLine + 1 || currentLine == targetLine + 2 || currentLine == targetLine + 3 || currentLine == targetLine + 4 || currentLine == targetLine + 5) {
        } else {
            tempFile << line << endl;
        }
        currentLine++;
    }

    file.close();
    tempFile.close();

    // Hapus file asli
    if (remove("account.txt") != 0) {
        cout << "Gagal menghapus file asli." << endl;
        return;
    }

    // Ganti nama file sementara menjadi nama file asli
    if (rename("temp.txt", "account.txt") != 0) {
        cout << "Gagal mengganti nama file." << endl;
        return;
    }
}

string User::mulai(){ //Untuk melakukan registrasi atau login
    bool check;
    int choice = firstMenu();
    if(choice == 1){
        check = loginAsMember();
        if (!check){
            choice = 2;
            check = regist();
            while(!check){
                check = regist();
            }
            cout << "Masukkan Nama: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nama);
            cout << "Masukkan Email: " << endl;
            cin >> email;
            cout << "Masukkan No Telepon: " << endl;
            cin >> noTelp;
            cout << "Masukkan NIK: " << endl;
            cin >> idNumber;
            cout << "Register berhasil, silahkan login!" << endl;
            ofstream file("account.txt", ios::app);
            file << username << "\n" << password << "\n" << nama << endl;
            file << email << "\n" << noTelp << "\n" << idNumber << "\n" << endl;
            file.close();

            check = loginAsMember();
            if(check){
                username = "-1"; password = "-1"; 
                return checkUsername; // Login Berhasil
            }
        } else {
            return checkUsername;
        }
    } else if (choice == 2) {
        check = regist();
        while(!check){
            check = regist();
        }
        cout << "Masukkan Nama: " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nama);
        cout << "Masukkan Email: " << endl;
        cin >> email;
        cout << "Masukkan No Telepon: " << endl;
        cin >> noTelp;
        cout << "Masukkan NIK: " << endl;
        cin >> idNumber;
        cout << "Register berhasil, silahkan login!" << endl;
        ofstream file("account.txt", ios::app);
        file << username << "\n" << password << "\n" << nama << endl;
        file << email << "\n" << noTelp << "\n" << idNumber << "\n" << endl;
        file.close();
        
        check = loginAsMember();
        if(check){
            username = "-1"; password = "-1"; 
            return checkUsername;
        }
    } else if (choice == 3){
        check = loginAsAdministrator();
        if(check){
            username = "-1"; password = "-1"; 
            return checkUsername; // Login Administrator
        }
    }

    return 0;
}

