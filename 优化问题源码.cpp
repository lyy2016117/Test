// 
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

/*
	实现一个排序算法
*/

void ExchangeForMax(unsigned int *data1, unsigned int *data2)
{
	unsigned int temp = 0;

	if (*data2 > *data1)
	{
		temp = *data1;
		*data1 = *data2;
		*data2 = temp;
	}
}

void BubbleSort(unsigned int data[], unsigned int data_lenth)           
{
	unsigned int i_loop, k_loop;

	for (i_loop = 0; i_loop < data_lenth - 1; i_loop++)                    //
	{
		for (k_loop = 0 ; k_loop < data_lenth - i_loop; k_loop++)
		{
			ExchangeForMax(&data[k_loop], &data[k_loop + 1]);               //
		}
	}
}

/*
	最优化问题：
	设运输车的最大运力为M，现有n件货物，每件货物的价值和占用的运力分别是vi和mi，均为整数。其中，M<∑m_i ，
	即无法装下所有货物。请设计一个算法，从n件货物中选出价值最高的部分，作为要被运输的货物。
	编程语言不限，具体编码时，M不超过65535，n不超过255。
	例如，最大运力为5，有三件货物，占用运力分别为3、2、2，价值分别为4、2、1，则应当运输第1件和第2件。

	Solution: 
	At first, algorithm should rank the data form large value to small value; then, algorithm
	should traverse the array and choose the data as long as their weight less than M.
	
*/
struct cargo
{
	unsigned int v;   //value of cargo
	unsigned int m;   //
};

/*BubbleSorting...*/
void ExchangeForMaxValue(struct cargo *data1, struct cargo *data2)
{
	struct cargo temp;

	if (data2->v > data1->v)        //from large value to small value
	{
		temp.v = data1->v;
		temp.m = data1->m;

		data1->v = data2->v;
		data1->m = data2->m;

		data2->v = temp.v;
		data2->m = temp.m;
	}
}

void BubbleSortStructCargo(struct cargo data[], unsigned int data_lenth)
{
	unsigned int i_loop, k_loop;

	for (i_loop = 0; i_loop < data_lenth-1 ; i_loop++)                         
	{
		for (k_loop = 0 ; k_loop < data_lenth-i_loop; k_loop++)
		{
			ExchangeForMaxValue(&data[k_loop], &data[k_loop + 1]);               //
		}
	}
}



/**
  * @brief               traversing and determining the cargo to be transported, and load them into the heap memory.
  * @param  M:           maximum weight that the car can load
  * @param  m_cargo[]:   prepared cargo data
  * @param  n:           quantity of entire cargo
  * @retval              cargo index, which mark the chosen cargo, stored in the heap memory
  */
unsigned short sum = 0;
unsigned char* CarryingCargo(unsigned short M, struct cargo m_cargo[], unsigned char n)
{
	unsigned char k = 0;
	unsigned char i = 1;
	unsigned char m_loop = 1;
	
	/*
	   At first, allocating heap memory to contain the index, 
	   caller must remember to free the memory
	*/
	unsigned char *buffer_index = (unsigned char *)malloc(n+1);     
	memset(buffer_index, 0, n+1);

	/*
	   To make sure the chosen cargo is the most valuable, 
	   ranking the cargo_data from large value to small value,
	*/
	BubbleSortStructCargo(m_cargo, n);    

	/*
	   Traversing the array, and determining the index k,
	   because a single element of cargo[] could weight over M.

	   For example, when M=8, cargo[]={20, 15, 7, ...},
	   algorithm must start from the 7 which is smaller than 8. 
	*/
    for (; k < n; ++k)
	{
	    if (m_cargo[k].m > M)                               /*by (m_cargo[k].m < M)  determining the k*/
		{
			continue;                                      /*continue to find the right one*/
		}
		
		break;                                             /*getting the starting point to process*/
	}

	/*Starting to process the cargo from the k point*/
	for (i = 0; i < n - k; i++, m_loop++)
	{
		if ((sum + m_cargo[k + i].m) < M)        /*trying to find the right one*/
		{
			sum += m_cargo[k + i].m;
			buffer_index[m_loop] = k+i;
			continue;
		}
		else
		{
			--m_loop;
			continue;
		}
	}

	buffer_index[0] = m_loop -1;
	
	return buffer_index;
}

/*random test data set*/
struct cargo Cargo_Stuff[] = { {12,10},{11,5},{6,24},{23,14},{5,7},{16,3},{7,16},     \
                                  {20, 2}, { 10,1 }, { 4,1 }, { 97,54 }, { 67,12 }, {34,78} };

int main()
{
	cout << "\nAt first, please enter the capacity of the truck:\n";
	unsigned short Cargo_truck;
	cin >> Cargo_truck;
	printf( "\nThe capacity of truck is %d:\n\n\n", Cargo_truck);


	printf("There are %d cargo and the raw cargo is:\n", sizeof(Cargo_Stuff) / sizeof(struct cargo));
	printf("Index\t\t  value\t\t  weight \n");
	for (int i_loop = 0; i_loop < sizeof(Cargo_Stuff) / sizeof(struct cargo); i_loop++)
	{
		printf("%d\t\t  %d\t\t  %d \n", 
			  i_loop, Cargo_Stuff[i_loop].v, Cargo_Stuff[i_loop].m); 
	}


	/*beginning to process and load the cargo data*/
	unsigned char* cargo_index = CarryingCargo(Cargo_truck, 
		                                       Cargo_Stuff,        
		                                       sizeof(Cargo_Stuff)/sizeof(struct cargo));



	   cout << "\nThe sorted cargo is:\n";
	   printf("Index\t\t  value\t\t  weight \n");
	   for (int i_loop = 0; i_loop < sizeof(Cargo_Stuff) / sizeof(struct cargo); i_loop++)
	   {
		   printf("%d\t\t  %d\t\t  %d \n",
			      i_loop, Cargo_Stuff[i_loop].v, 
			      Cargo_Stuff[i_loop].m);
	   }



	   printf("\nThere is %d cargo which should be loaded and    \
		     \nthe total weight of loaded cargo is %d.\n", cargo_index[0], sum);

	   sum = 0;

	   cout << "\n And the cargo should be loaded and marked by index is:\n";
	   unsigned char* pchar = cargo_index;
	   for (int i_loop = 1; i_loop <= cargo_index[0]; i_loop++)
	   {
		   sum = sum + Cargo_Stuff[cargo_index[i_loop]].m;
		   printf("%d>>> Index = %d   Cargo_Stuff[%d].m = %d  sum = %d\n", i_loop, 
			                                                               cargo_index[i_loop], 
			                                                               cargo_index[i_loop], 
			                                                               Cargo_Stuff[cargo_index[i_loop]].m, 
			                                                               sum);
	   }

	   free(cargo_index);
	   pchar = cargo_index = NULL;

	   cout << "\nEnter 'q' or 'Q' to quit.\n";
	   char quit = 0;
	   while (1)
	   {
		   cin >> quit;
		   if (quit=='q'||quit == 'Q')
		   {
			   return 0;
		   } 
		   else
		   {
			   cout << "Please try again.\n";
		   }
	   }

	return 0;
}