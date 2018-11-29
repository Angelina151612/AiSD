#pragma once

#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string>

template <typename T>
class Tree{
public:
	void read_elem(); 
public:
	T elem;			//элемент
	Tree* f_son; 	//указатель на первого сына
	Tree* next_bro; //указатель на первого брата
};

template <typename T>
void Tree<T>::read_elem(){	
	char c;
	for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar()); //игнорирование пробелов
	if(c == '\n' || c == EOF){
		std::cout << "Incorrect input!" << std::endl;
		exit(1);
	}
	else
		ungetc(c, stdin);
	std::cin >> elem;
	return;
}

template <typename T>
void read_tree(Tree<T>* root, Tree<T>* bro_pos, short lvl){
	char c;
	while(1){
		root->read_elem();

		for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar()); //игнорирование пробелов

		if(c == ')'){ 														  //поддерево закончилось 
			root->f_son = NULL;
			for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar());
			if(lvl){
				if(c == '('){												 //есть братья (a(b)(
					Tree<T>* bro = new Tree<T>;
					bro_pos->next_bro = bro;
					read_tree(bro, bro, lvl);
					return;
				}
				if(c == ')'){				//братьев нет (a(b))
					root->next_bro = NULL;
					ungetc(c, stdin);
					return;
				}
				std::cout << "Incorrect input!" << std::endl;
				exit(1);
			}
			else{  //если нулевой уровень
				if(c == '('){
					Tree<T>* bro = new Tree<T>;
					bro_pos->next_bro = bro;
					read_tree(bro, bro, lvl);
					return;
				}
				if(c != EOF && c != '\n'){
					std::cout << "Incorrect input!" << std::endl;
					exit(1);
				}
				else{
					root->next_bro = NULL;
					ungetc(c, stdin);
				}
				return;
			}
		}
		if(c == '('){ // есть сыновья
			Tree<T>* son = new Tree<T>;
			root->f_son = son;
				
					read_tree(son, son, lvl+1); //опускаемся на уровень ниже,т.к. нашли сыновей
					for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar());
				
		}
		if(c == ')'){ //поддерево закончилось
			for(c = getchar(); c == ' ' && c != '\n' && c != EOF; c = getchar());
			if(lvl){
				if(c == '('){ //могут быть братья
					Tree<T>* bro = new Tree<T>;
					bro_pos->next_bro = bro;
					read_tree(bro, bro, lvl);
					return;
				}
				if(c == ')'){
					root->next_bro = NULL;
					ungetc(c, stdin);
					return;
				}
				std::cout << "Incorrect input!" << std::endl;
				exit(1);
			}
			else{
				if(c == '('){ 
					Tree<T>* bro = new Tree<T>;
					bro_pos->next_bro = bro;
					read_tree(bro, bro, lvl);
					return;
				}
				if(c != EOF && c != '\n'){
					std::cout << "Incorrect input!" << std::endl;
					exit(1);
				}
				else{
					root->next_bro = NULL;
					ungetc(c, stdin);
				}
				return;
			}
		}
		std::cout << "Incorrect input!" << std::endl;
		exit(1);
	}
}

template <typename T>
void printSubBT(Tree<T>* root, const std::string& prefix){    //вывод БД
    if(!root->f_son && !root->next_bro) //если закончилось
        return;

    std::cout << prefix;
    std::cout <<  "├── ";

    if(root->next_bro){					//правый сын				
        std::string newPrefix = prefix + "│   ";
        std::cout << root->next_bro->elem << std::endl;
        printSubBT(root->next_bro, newPrefix);
    }
    else
    	std::cout << "#" << std::endl;

    if(root->f_son){						
        std::cout << prefix << "└── " << root->f_son->elem << std::endl;	//левый сын
        printSubBT(root->f_son, prefix + "    ");
    }
    else
    	std::cout << prefix << "└── #" << std::endl;
}

template <typename T>
void printBT(Tree<T>* root){ // вывод корня БД
    std::cout << root->elem << std::endl;
    printSubBT(root, "");
    std::cout << std::endl;
}

template <typename T>
void printSubF(Tree<T>* root, const std::string& prefix){	//вывод леса
    Tree<T>* printed_bro = root;	
    while(1){
    	Tree<T>* tmp;
    	for(tmp = root; tmp->next_bro; tmp = tmp->next_bro){
    		if(printed_bro && tmp->next_bro == printed_bro)
    			break;
    	}
    	std::cout << prefix;
    	if(root != tmp){
    		std::cout <<  "├── ";
        	std::string newPrefix = prefix + "│   ";
            std::cout << tmp->elem << std::endl;
            if(tmp->f_son)
        		printSubF(tmp->f_son, newPrefix);
        }
        else{
        	std::cout <<  "└── " << root->elem << std::endl;
        	if(root->f_son){
        		printSubF(root->f_son, prefix + "    ");
        	}
        	return;
        }
        printed_bro = tmp;
    }
}

template <typename T>
void printF(Tree<T>* root){			//вывод корня дерева леса
	std::cout << root->elem << std::endl;
	if(root->f_son){
		printSubF(root->f_son, "");
		std::cout << std::endl;
	}
	Tree<T>* tmp;	//след дерево леса
	for(tmp = root->next_bro; tmp; tmp = tmp->next_bro){//след дерево леса
		std::cout << tmp->elem << std::endl;
		if(tmp->f_son){
			printSubF(tmp->f_son, "");
			std::cout << std::endl;
		}
	}
}
