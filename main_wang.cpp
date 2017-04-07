#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "timer.hpp"

#define NOISY 0

typedef unsigned short I16;
typedef unsigned char I8;

class Lex_perm {
	public:
	I8 number[10];
	char out[12];
	I8 length;
	Lex_perm(I8 l) {
		memset(number, 0, sizeof(number));
		length = l;
	}
	bool next_mnum();
	void num_to_list();
	void print_number();
	void set_number(I8 * set);
	void generate_all();
};
class Incre_perm {
	public:
	I8 number[10];
	char out[12];
	I8 length;
	Incre_perm(I8 l) {
		memset(number, 0, sizeof(number));
		length = l;
	}
	bool next_mnum();
	void num_to_list();
	void print_number();
	void set_number(I8 * set);
	void generate_all();
};
class Decre_perm {
	public:
	I8 number[10];
	char out[12];
	I8 length;
	Decre_perm(I8 l) {
		memset(number, 0, sizeof(number));
		length = l;
	}
	bool next_mnum();
	void num_to_list();
	void print_number();
	void set_number(I8 * set);
	void generate_all();
};
class SJT_perm {
	public:
	I8 number[10];
	char out[12];
	I8 length;
	SJT_perm(I8 l) {
		memset(number, 0, sizeof(number));
		length = l;
	}
	bool next_mnum();
	void num_to_list();
	void print_number();
	void set_number(I8 * set);
	void generate_all();
};

inline I16 BitCount(I16 u)
{
     I16 uCount;
     uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
     return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}

inline size_t bsf(size_t input) {
	size_t pos;
#ifdef _WIN32
	__asm 
	{
		mov ebx, input
		bsf eax, ebx
		mov pos, eax
	};
#elif __linux__
	__asm__ ("bsf %1, %0" : "=r" (pos) : "rm" (input));
#endif
	return pos;
}

void Lex_perm::print_number() {
	for (int i = length - 1; i >= 0; --i)
		printf("%d\t", number[i]);
	std::cout << std::endl;
}

void Incre_perm::print_number() {
	for (int i = length - 1; i >= 0; --i)
		printf("%d\t", number[i]);
	std::cout << std::endl;
}

void Decre_perm::print_number() {
	for (int i = length - 1; i >= 0; --i)
		printf("%d\t", number[i]);
	std::cout << std::endl;
}

void SJT_perm::print_number() {
	for (int i = length - 1; i >= 0; --i)
		printf("%d\t", number[i]);
	std::cout << std::endl;
}

void Lex_perm::set_number(I8 * set) {
	memcpy(number, set, sizeof(number));
}

void Incre_perm::set_number(I8 * set) {
	memcpy(number, set, sizeof(number));
}

void Decre_perm::set_number(I8 * set) {
	memcpy(number, set, sizeof(number));
}

void SJT_perm::set_number(I8 * set) {
	memcpy(number, set, sizeof(number));
}

bool Lex_perm::next_mnum() {
	I8 iter = 0;
	while (iter < length && (++number[iter]) > (iter+1)) {
		number[iter] = 0;
		iter++;
	}
	if (iter == length)
		return false;
	else
		return true;
}

bool Incre_perm::next_mnum() {
	I8 iter = 0;
	while (iter < length && (++number[iter]) > (iter+1)) {
		number[iter] = 0;
		iter++;
	}
	if (iter == length)
		return false;
	else
		return true;
}

bool Decre_perm::next_mnum() {
	I8 iter = 0;
	while (iter < length && (++number[iter]) > (length-iter)) {
		number[iter] = 0;
		iter++;
	}
	if (iter == length)
		return false;
	else
		return true;
}

bool SJT_perm::next_mnum() {
	I8 iter = 0;
	while (iter < length && (++number[iter]) > (length-iter)) {
		number[iter] = 0;
		iter++;
	}
	if (iter == length)
		return false;
	else
		return true;
}

void Lex_perm::num_to_list() {
	I16 used=0;
	I8 iter = length - 1;
	while (iter) {
		I8 should_count = 1;
		I16 bias = number[iter] + 1;
		I16 delta_bias;
		I16 flag = ~0 << bias;
		I16 mask = ~flag;
		I16 slots = used & mask;
		bias = __popcnt16(slots);
		delta_bias = bias;
		should_count += delta_bias;
		while (delta_bias)
		{
			I16 flag1 = flag << delta_bias;
			mask = ~flag1;
			flag = flag1;
			slots = used & mask;
			I16 bias_t = __popcnt16(slots);
			delta_bias = bias_t - bias;
			bias = bias_t;
			should_count += delta_bias;
		}
		I8 out_num = number[iter]+should_count;
		out[length - iter - 1] = '0'+out_num;
		used |= 1 << (out_num-1);
		iter--;
	}
	out[length] = '0'+1+bsf(~used);
	out[length+1] = '\0';
}

void Incre_perm::num_to_list() {
	I16 used = 0;
	I8 iter = length - 1;
	while (iter) {
		I16 bias = number[iter] + 1;
		I8 should_count = bias;
		I16 delta_bias;
		I16 flag = ~0 << bias;
		I16 mask = ~flag;
		I16 slots = used & mask;
		bias = __popcnt16(slots);
		delta_bias = bias;
		should_count += delta_bias;
		while (delta_bias)
		{
			I16 flag1 = flag << delta_bias;
			mask = ~flag1;
			flag = flag1;
			slots = used & mask;
			I16 bias_t = __popcnt16(slots);
			delta_bias = bias_t - bias;
			bias = bias_t;
			should_count += delta_bias;
		}

		int out_pos = length - should_count + 1;
		out[out_pos] = '0'+iter+2;
		used |= 1 << (should_count-1);
		iter--;
	}
	out[length-bsf(~used)] = '1';
	out[length+1] = '\0';
}

void Decre_perm::num_to_list() {
	I16 used = 0;
	I8 iter = length - 1;
	while (iter) {
		I16 bias = number[length-1-iter] + 1;
		I8 should_count = bias;
		I16 delta_bias;
		I16 flag = ~0 << bias;
		I16 mask = ~flag;
		I16 slots = used & mask;
		bias = __popcnt16(slots);
		delta_bias = bias;
		should_count += delta_bias;
		while (delta_bias)
		{
			I16 flag1 = flag << delta_bias;
			mask = ~flag1;
			flag = flag1;
			slots = used & mask;
			I16 bias_t = __popcnt16(slots);
			delta_bias = bias_t - bias;
			bias = bias_t;
			should_count += delta_bias;
		}

		int out_pos = length - should_count + 1;
		out[out_pos] = '0'+iter+2;
		used |= 1 << (should_count-1);
		iter--;
	}
	out[length-bsf(~used)] = '1';
	out[length+1] = '\0';
}

void SJT_perm::num_to_list() {
	I16 used = 0;
	I8 iter = length - 1;
	while (iter) {
		I16 bias = number[length-1-iter] + 1;
		bool dir = 0;
		if (iter % 2) 
			dir = number[length-iter] % 2;
		else if (iter != 0)
			dir = (number[length-iter]+number[length-iter+1]) % 2;
		if (!dir || iter == 0)
		{
			I8 should_count = bias;
			I16 delta_bias;
			I16 flag = ~0 << bias;
			I16 mask = ~flag;
			I16 slots = used & mask;
			bias = __popcnt16(slots);
			delta_bias = bias;
			should_count += delta_bias;
			while (delta_bias)
			{
				I16 flag1 = flag << delta_bias;
				mask = ~flag1;
				flag = flag1;
				slots = used & mask;
				I16 bias_t = __popcnt16(slots);
				delta_bias = bias_t - bias;
				bias = bias_t;
				should_count += delta_bias;
			}
			int out_pos = length - should_count + 1;
			out[out_pos] = '0'+iter+2;
			used |= 1 << (should_count-1);
		}
		else
		{
			I8 should_count = bias;
			I16 delta_bias;
			I16 flag = ~(~0 << (length-bias+1));
			I16 mask = ~flag;
			I16 slots = used & mask;
			bias = __popcnt16(slots);
			delta_bias = bias;
			should_count += delta_bias;
			while (delta_bias)
			{
				I16 flag1 = flag << delta_bias;
				mask = ~flag1;
				flag = flag1;
				slots = used & mask;
				I16 bias_t = __popcnt16(slots);
				delta_bias = bias_t - bias;
				bias = bias_t;
				should_count += delta_bias;
			}
			I8 out_pos = should_count - 1;
			out[out_pos] = '0'+iter+2;
			used |= 1 << (length-out_pos);
		}
		iter--;
	}
	out[length-bsf(~used)] = '1';
	out[length+1] = '\0';
}

void Lex_perm::generate_all() {
	do {
		num_to_list();
		if (NOISY)
			printf("%s\n", out);
	}while (next_mnum());
}

void Incre_perm::generate_all() {
	do {
		num_to_list();
		if (NOISY)
			printf("%s\n", out);
	}while (next_mnum());
}

void Decre_perm::generate_all() {
	do {
		num_to_list();
		if (NOISY)
			printf("%s\n", out);
	}while (next_mnum());
}

void SJT_perm::generate_all() {
	do {
		num_to_list();
		if (NOISY)
			printf("%s\n", out);
	}while (next_mnum());
}

void test()
{
	SJT_perm perm(3);
	perm.generate_all();
}

int main(int argc, char ** argv)
{
	//test();
	double start, end;
	int num = 4;
	if (argc == 2)
		num = atoi(argv[1])-1;
	Lex_perm lex(num);
	Incre_perm incre(num);
	Decre_perm decre(num);
	SJT_perm sjt(num);
	std::cout << "Lexo out: " << std::endl;
	start = get_time();
	lex.generate_all();
	end = get_time();
	std::cout << "Takes " << end-start << "s" << std::endl;
	std::cout << "Incre out: " << std::endl;
	start = get_time();
	incre.generate_all();
	end = get_time();
	std::cout << "Takes " << end-start << "s" << std::endl;
	std::cout << "Decre out: " << std::endl;
	start = get_time();
	decre.generate_all();
	end = get_time();
	std::cout << "Takes " << end-start << "s" << std::endl;
	std::cout << "STJ out: " << std::endl;
	start = get_time();
	sjt.generate_all();
	end = get_time();
	std::cout << "Takes " << end-start << "s" << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
