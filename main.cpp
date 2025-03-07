// #define SDL_MAIN_HANDLED
#include <iostream>
// #include <SDL.h>
// #include <SDL_ttf.h>
// #include <SDL_image.h>
#include <filesystem>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

class Node{
	public:
		fs::path Path;
		Node* next;
		Node* prev;

		Node(fs::path Path) : next(nullptr), prev(nullptr){
			this->Path = Path;
		}
};

class History{
	public:
		Node* head;
		Node* current;
		bool running;

		History() : head(nullptr), current(nullptr), running(true){}

		void Add(fs::path Path){
			Node* newNode = new Node(Path);
			if(!head){
				head = newNode;
				current = newNode;
			}else{
				current->next = newNode;
				newNode->prev = current;
				current = newNode;
			}
		}

		void setCurrentPath(){
			if(current){
				fs::current_path(current->Path);
			}
		}

		void PrevPath(){
			current = current->prev;
			setCurrentPath();
		}

		void NextPath(){
			current = current->next;
			setCurrentPath();
		}

		void update(bool isPathChange){
			if(isPathChange){
				Node* temp = head;
				while(temp->next != current && temp){
					temp = temp->next;
				}
				temp->next = current;
				current->prev = temp;
			}
		}

		void run(){
			int ops;
			string path;
			while(running){
				cout << "Masukkan Pilihan: " << endl;
				cout << "1. Next" << endl;
				cout << "2. Previous" << endl;
				cout << "3. Open Dir" << endl;
				cout << "4. Display Current" << endl;
				cout << "5. Exit" << endl;
				cout << current->Path << ": ";
				cin >> ops;
				switch (ops){
					case 1 : NextPath();
						break;
					case 2 : PrevPath(); break;
					case 3 : cin >> path ; Add(path) ; NextPath() ; break;
					case 4 : 
						for(const auto& entry : fs::directory_iterator(current->Path)){
							cout << entry.path() << endl;
						}
						break;
					case 5 : running = false;
						break;
					default : cout << "Invalid Input!" << endl;
						break;
					}
			}
		}
};

int main(){
	History H;
	H.Add("D:/");
	H.run();

	return 0;
}

