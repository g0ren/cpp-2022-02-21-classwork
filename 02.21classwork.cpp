#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/*
 * Пользователь вводит строку
 * потом мы у пользователя спрашиваем символ
 * а функция возвращает количество этого символа
 */
int numberOfChars(char *l, char k) {
	int n { };
	while (*l != 0) {
		if (*l == k)
			n++;
		l++;
	}
	return n;
}

void replace(char *l, char s, char e) {
	while (*l != 0) {
		if (*l == s)
			*l = e;
		l++;
	}
}

/*
 *  Написать функцию, принимающую строку и разворачивающую сокращения с использованием {}:
 а) без вложенных конструкций, например, строка
 abc{def,gh,ijkl}mn
 разворачивается в
 abcdefmn,abcghmn,abcijklmn
 */
int numberOfCommas(char *l) {
	int n { };
	while (*l != 0) {
		if (*l == ',')
			n++;
		l++;
	}
	return n;
}

char* beforeComma(char *l) {
	char *comma = strchr(l, ',');
	if (comma == nullptr)
		return l;
	char *before = new char[strlen(l)] { };
	char *read, *write;
	read = l;
	write = before;
	while (read < comma) {
		*write = *read;
		read++;
		write++;
	}
	return before;
}

char* afterComma(char *l) {
	char *comma = strchr(l, ',');
	if (comma == nullptr)
		return nullptr;
	char *after = new char[strlen(l)] { };
	char *read, *write;
	read = comma + 1;
	write = after;
	while (*read != 0) {
		*write = *read;
		read++;
		write++;
	}
	return after;
}

char* getInside(char *l) {
	char *inside = new char[strlen(l)] { };
	char *open = strchr(l, '{');
	char *close = strrchr(l, '}');
	char *read { open }, *write { inside };
	while (write < close) {
		*write = *read;
		read++;
		write++;
	}
	return inside;
}

char* expand(char *l) {
	char *open { }, *close { };
	open = strchr(l, '{');
	close = strrchr(l, '}');
	if (open == nullptr || close == nullptr)
		return l;

	char *before = new char[strlen(l)] { };
	char *after = new char[strlen(l)] { };
	char *inside = new char[strlen(l)] { };

	char *read, *write;
	read = l;
	write = before;
	while (read < open) {
		*write = *read;
		read++;
		write++;
	}
	read++;
	write = inside;
	while (read < close) {
		*write = *read;
		read++;
		write++;
	}
	read++;
	write = after;
	while (*read != 0) {
		*write = *read;
		read++;
		write++;
	}

	int size = (strlen(before) + strlen(after) + strlen(inside))
			* numberOfCommas(inside);
	char *result = new char[size] { };

	while (afterComma(inside) != nullptr) {
		char *part = beforeComma(inside);
		inside = afterComma(inside);
		strcat(result, before);
		strcat(result, part);
		strcat(result, after);
		strcat(result, ",");
		delete[] part;
	}
	strcat(result, before);
	strcat(result, beforeComma(inside));
	strcat(result, after);
	delete[] before;
	delete[] after;
	delete[] inside;
	return result;
}

int main() {
	char *pc = new char[256] { };
	//char c { };
	cout << "Enter line" << endl;
	cin.getline(pc, 256);
	//cout << beforeComma(pc) << endl << afterComma(pc) << endl;
	//cout << "Enter char" << endl;
	//cin >> c;
	//cout << numberOfChars(pc, c) << endl;
	cout << expand(pc);

	return 0;
}

