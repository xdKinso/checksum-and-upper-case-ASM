#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void uppercase(string& str)
{
	auto data = str.c_str();
	auto len = str.length();
	_asm
	{
		//load length into ecx register
		//used for loop counting 
		mov ecx, len
		//load the memory location into ebx register
		//used to access correct element in array
		mov ebx, data

		start_loop :
		//move byte in memory location ebx +exc -1 into al register
			mov al, byte ptr[ebx + ecx - 1]
			// compare al register to z
			cmp al, 'z'
			jg end_loop
			//compare al register to a
			cmp al, 'a'
			jl end_loop
			sub al, 32
			mov byte ptr[ebx + ecx - 1], al

		end_loop :
			loop start_loop
	}
}int count_letters(string& str)
{
	auto data = str.c_str();
	auto len = str.length();
	int count = 0;
	__asm
	{
			mov ecx, len
			mov ebx, data
		start_loop:
			mov al, byte ptr[ebx + ecx - 1]
			cmp al, 'A'
			jl end_loop
			cmp al, 'z'
			jg end_loop
			cmp al, 'Z'
			jl increment
			cmp al, 'a'
			jg increment 
			jmp end_loop
		increment:
			mov eax, count
			inc eax 
			mov count, eax
		end_loop:
			loop start_loop
	}
	return count;
}


int main(int argc, char** argv)
{
	string test;
	cout << "enter your name" << endl;
	cin >> test;
	uppercase(test);
	cout << "Your name is: " << test << endl;
	cout << "there are " <<count_letters(test) <<"  letters in your name" << endl;
	return 0;
}