#include <iostream>
#include <string>
#include "t.h"
#include "queue.h"

template <typename T>
void delete_forest(Tree<T>* root){
	if(!root)
		return;
	delete_forest(root->f_son);
	delete_forest(root->next_bro);
	delete root;
	return;
}

int main(){
	Tree<char>* Head = new Tree<char>;
	char c;
	std::cout << "Введите лес деревьев. Деревья ввести в виде (a(b)(c(d))). Пробелы игнорируются." << std::endl;
	for(c = getchar(); c == ' ' && c != '\n'; c = getchar());

	if(c == EOF || c == '\n'){
		std::cout << "Некорректный ввод!" << std::endl;
		exit(1);
	}
	while(c != EOF && c != '\n'){
		if(c != '('){
			std::cout << "Некорректный ввод!" << std::endl;
			exit(1);
		}
		read_tree(Head, Head, 0);
		std::cout << std::endl;
		std::cout << "Лес успешно считан!" << std::endl;
		for(c = getchar(); c == ' ' && c != '\n'; c = getchar());
	}
	
	std::cout << std::endl;
	std::cout << "Изображение повернуто на 90 градусов таким образом, что левый сын ниже правого."<< std::endl;
	std::cout << std::endl << "Лес:" << std::endl;
	printF(Head);
	std::cout << std::endl << "Бинарное дерево:" << std::endl;
	printBT(Head);
	std::cout << "Обход леса в ширину: ";

	Queue_Head<Tree<char> *> q; // очередь для хранения указателей на вершины
    Tree<char>* cur; 			// указатель на вершину  
    q.push(Head); 	// записываем начальные вершины в очередь
    if(Head->next_bro){
    	for(cur = Head->next_bro; cur; cur = cur->next_bro)
            q.push(cur);
    }
    
    while(!q.is_empty()){
        cur = q.give_back();
        std::cout << cur->elem << " ";
        q.del_back();
        if(cur->f_son)
	        for(cur = cur->f_son; cur; cur = cur->next_bro)
                q.push(cur);
    }
    std::cout<< '.' << std::endl;
	delete_forest(Head);

    return 0;
}

//(a(b(d))(c))(e(f)(g(i))(k(j)))