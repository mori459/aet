#include <iostream>
#include <string>
#include <limits>


//glabal variables and dynamic arrays
int size = 10;
int* id_arr = new int[size];
std::string* name_arr = new std::string[size];
int* count_arr = new int[size];
double* price_arr = new double[size];

double cash = 3423423.0;
double cash_income = 0.0, card_income = 0.0, total_income = 0.0;


//reciept glabal variables and dynamic arrays
int reciept_size = 1;
std::string* name_reciept = new std::string[reciept_size];
int* count_reciept = new int[reciept_size] {};
double* price_reciept = new double[reciept_size];


//main func
void Start();
void CreateStorage();
void Shop();
void PrintStorage();
void Selling();
void AddElementToReciept(int id, int count);
void PrintReciept();
void ChangePrice();
void AddToStorage();
void RemoveFormStorage();
void ChangeStorage();
void AddElementToEnd();
void DeleteByIndex();
void DeleteMainArrays();
void CashStatus();
int TabCount(std::string* arr, int cur_size, std::string headliner);
std::string TabSepparator(std::string str, int tab_len);


template <typename ArrayType>
void FillArray(ArrayType static_arr, ArrayType dyn_arr, int size);

int main()
{
	setlocale(LC_ALL, "ru");
	Start();


	DeleteMainArrays();
	return 0;
}



void Start()	//@prog start up
{
	std::string admin_login = "admin";
	std::string admin_password = "pass";
	std::string login, password;
	int choice;
	bool exit = false;

	do	//@security
	{
		system("cls");
		std::cout << "�������� �������� ������\n\n";
		std::cout << "������� �����: ";		//auth
		std::getline(std::cin, login);
		std::cout << "������� ������: ";
		std::getline(std::cin, password);

		if (login != admin_login || password != admin_password)	//error in case of incorrect input
		{
			system("cls");
			std::cerr << "�������� ������ ��� �����\n";
			std::cout << "����������� ��� ���? \n1 - ��\n2 - ����� �� ���������\n";
			std::cin >> choice;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (choice == 2)
			{
				exit = true;	//prog exit
			}
		}
		else	//successeful auth
		{
			exit = true;
			int storagetype_choice;		//@main menu
			do
			{
				system("cls");
				std::cout << "�������� �������� ������\n\n";
				std::cout << "������� ������� ������: \n1 - ������� �����\n2 - ������� ����� �������\n";
				std::cin >> storagetype_choice;
			} while (storagetype_choice < 1 || storagetype_choice > 2);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (storagetype_choice == 1)
			{
				CreateStorage();		//template storage
				Shop();
			}
			else if (storagetype_choice == 2)
			{
				std::cout << "� ����������\n";		//custom storage
			}
			else
			{
				std::cerr << "Error storagetype_choice\n";
			}
		}
	} while (!exit);
}

void CreateStorage()	//@template storage func
{
	const int static_size = 10;
	int id[static_size]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::string name[static_size]{ "����������", "�� �������", "�������� �������", "������� ��������", "�� �����", "MP40", "Sturmgewehr 44", "�������� M1918", "��������� ������ 1873", "�����" };
	int count[static_size]{ 234, 5346, 24, 543, 532, 5434, 543, 437, 4764, 4744 };
	double price[static_size]{ 345.0, 34.0, 534.0, 53.0, 45.0, 5334.0, 5.0, 54.0, 5675.0, 453.0 };

	FillArray(id, id_arr, static_size);			//static to dynamic
	FillArray(name, name_arr, static_size);
	FillArray(count, count_arr, static_size);
	FillArray(price, price_arr, static_size);

}

void Shop()	//@main menu
{
	char choice;
	while (true)
	{
		do
		{
			system("cls");
			std::cout << "�������� �������� ������\n\n";
			std::cout << "1 - �������� �����\n";
			std::cout << "2 - ������  �������\n";
			std::cout << "3 - ������� ����\n";
			std::cout << "4 - �������� �����\n";
			std::cout << "5 - ��������� �����\n";
			std::cout << "6 - �������� �����\n";
			std::cout << "7 - �������� �����\n";
			std::cout << "0 - ��������� �����\n";
			std::cin >> choice;

		} while (choice < 48 || choice > 55);

		if (choice == '1')
		{
			PrintStorage();		//storage continance showcase
		}
		else if (choice == '2')
		{
			Selling();
		}
		else if (choice == '3')
		{
			ChangePrice();
		}
		else if (choice == '4')
		{
			RemoveFormStorage();
		}
		else if (choice == '5')
		{
			AddToStorage();
		}
		else if (choice == '6')
		{
			ChangeStorage();
		}
		else if (choice == '7')
		{
			CashStatus();
		}
		else if (choice == '0')
		{
			break;
		}
		else
		{
			std::cerr << "Error\n";
		}



	}
}

void PrintStorage()	//@storage continance showcase func
{
	system("cls");
	std::cout << "�������� �������� ������\n\n";

	int sep_name_count = TabCount(name_arr, size, "�������� ������");

	std::cout << "ID\t" << "�������� ������" << TabSepparator("�������� ������", sep_name_count) << "���-��" << "\t\t" << "����\n";

	for (int i = 0; i < size; i++)
	{
		std::cout << id_arr[i] << "\t" << name_arr[i] << TabSepparator(name_arr[i], sep_name_count) << count_arr[i] << "\t\t" << price_arr[i] << "\n";
	}
	system("pause");
}

void Selling()
{
	int choice_id, choice_count;
	bool is_first = true;
	double total_sum = 0;
	char confirm;
	bool is_repeat = false;
	int repeat_id;



	while (true)
	{
		total_sum = 0;
		is_repeat = false;

		system("cls");
		std::cout << "�������� �������� ������\n�������\n\n";
		std::cout << "������� id ������: ";
		std::cin >> choice_id;
		if (choice_id < 1 || choice_id > size)
		{
			std::cerr << "Error\n";
			continue;
		}
		if (count_arr[choice_id - 1] > 0)
		{
			while (true)
			{
				std::cout << "�����: " << name_arr[choice_id - 1] << '\n';
				std::cout << "����: " << price_arr[choice_id - 1] << '\n';
				std::cout << "���-�� �� ������: " << count_arr[choice_id - 1] << "\n\n";
				std::cout << "������� ������: ";
				std::cin >> choice_count;
				if (choice_count < 1 || choice_count > count_arr[choice_id - 1])
				{
					std::cerr << "Error\n";
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cerr << "Error\n";
			continue;
		}

		std::cout << "����������� \n1 - ��\n2 - ���\n";
		std::cin >> confirm;

		if (confirm == '1')
		{


			if (is_first == true)
			{
				name_reciept[reciept_size - 1] = name_arr[choice_id - 1];
				count_reciept[reciept_size - 1] = choice_count;
				price_reciept[reciept_size] = double(price_arr[choice_id - 1] * choice_count);
				count_arr[choice_id - 1] = choice_count;
				total_sum += price_arr[choice_id - 1] * choice_count;
				is_first = false;
			}
			else
			{
				for (int i = 0; i < reciept_size; i++)
				{
					if (name_arr[choice_id - 1] == name_reciept[i])
					{
						is_repeat = true;
						repeat_id = i;
						break;
					}
				}
				if (is_repeat == true)
				{
					count_reciept[repeat_id] += choice_count;
					price_reciept[reciept_size] += price_arr[choice_id - 1] * choice_count;
					total_sum += price_arr[choice_id - 1] * choice_count;
				}
				else
				{
					AddElementToReciept(choice_id, choice_count);
					total_sum += price_arr[choice_id - 1] * choice_count;
				}
			}



		}
		else
		{
			continue;
		}

		system("cls");
		std::cout << "�������� �������� ������\n�������\n\n";
		std::cout << "������ ��� ���� �����?\n";
		std::cout << "1 - ��\n2 - ���\n";
		std::cin >> confirm;
		if (confirm == '1')
		{
			continue;
		}
		break;
	}

	PrintReciept();

	char pay;
	std::cout << "\n\n";
	std::cout << "1 - ��������\n2 - ������ ������\n\n";
	do
	{
		std::cin >> pay;
	} while (pay < 49 || pay > 50);
	if (pay == '1')
	{
		cash += total_sum;
		cash_income += total_sum;
		total_income += total_sum;
	}
	else if (pay == '2')
	{
		card_income += total_sum;
		total_income += total_sum;
	}

	std::cout << total_sum << "  � ������\n";
	system("pause");
}
void AddElementToReciept(int id, int count)
{
	std::string* name_temp = new std::string[reciept_size];
	int* count_temp = new int[reciept_size];
	double* price_temp = new double[reciept_size];

	for (int i = 0; i < reciept_size; i++)
	{
		name_temp[i] = name_reciept[i];
		count_temp[i] = count_reciept[i];
		price_temp[i] = price_reciept[i];
	}

	delete[]name_reciept;
	delete[]count_reciept;
	delete[]price_reciept;

	reciept_size++;
	name_reciept = new std::string[reciept_size];
	count_reciept = new int[reciept_size];
	price_reciept = new double[reciept_size];

	for (int i = 0; i < reciept_size - 1; i++)
	{
		name_reciept[i] = name_temp[i];
		count_reciept[i] = count_temp[i];
		price_reciept[i] = price_temp[i];
	}

	name_reciept[reciept_size - 1] = name_arr[id - 1];
	count_reciept[reciept_size - 1] += count;
	price_reciept[reciept_size - 1] += price_arr[id - 1] * count;
	count_arr[id - 1] = count;

	delete[]name_temp;
	delete[]count_temp;
	delete[]price_temp;
}
void PrintReciept()
{
	system("cls");
	std::cout << "�������� �������� ������\n��� ���\n\n";

	int sep_name_count = TabCount(name_reciept, reciept_size, "�������� ������");

	std::cout << "ID\t" << "�������� ������" << TabSepparator("�������� ������", sep_name_count) << "���-��" << "\t\t" << "����\n";

	for (int i = 0; i < reciept_size; i++)
	{
		std::cout << id_arr[i] << "\t" << name_reciept[i] << TabSepparator(name_reciept[i], sep_name_count) << count_reciept[i] << "\t" << price_arr[i] << "\n";
	}
	//system("pause");
}

void ChangePrice()
{
	int id;
	double new_price;
	do
	{
		std::cin >> id;
	} while (id < 1 || id > id_arr[size - 1]);

	std::cout << "\n\nChoice item: " << name_arr[id - 1] << " = " << price_arr[id - 1];
	do
	{
		std::cout << "\nnew_price";
		std::cin >> new_price;
	} while (new_price < 0.01 || new_price > 1000000);
	price_arr[id - 1] = new_price;
	std::cout << "success\n";
}

void RemoveFormStorage()
{

	int id;
	double count;
	do
	{
		std::cin >> id;
	} while (id < 1 || id > id_arr[size - 1]);

	std::cout << "\n\nChoice item: " << name_arr[id - 1] << " = " << price_arr[id - 1];
	do
	{
		std::cout << "\nnew_price";
		std::cin >> count;
	} while (count < 0 || count > count_arr[id - 1]);
	count_arr[id - 1] -= count;
	std::cout << "success\n";
}

void AddToStorage()
{
	int id;
	double count;
	do
	{
		std::cin >> id;
	} while (id < 1 || id > id_arr[size - 1]);

	std::cout << "\n\nChoice item: " << name_arr[id - 1] << " = " << price_arr[id - 1];
	do
	{
		std::cout << "\nnew_price";
		std::cin >> count;
	} while (count < 0 || count > count_arr[id - 1]);
	count_arr[id - 1] += count;
	std::cout << "success\n";
}

void ChangeStorage()
{
	char choice;
	do
	{
		system("cls");
		std::cout << "�������� �������� ������\n\n";
		std::cout << "1 - �������� ����� �� �����\n";
		std::cout << "2 - ������ ����� �� ������\n";
		std::cout << "0 - �����\n";
		std::cin >> choice;

	} while (choice < 48 || choice > 50);

	if (choice == '1')
	{
		AddElementToEnd();
	}
	else if (choice == '2')
	{
		DeleteByIndex();
	}
	else
	{
		std::cout << "�����\n";
		system("pause");
	}
}
void AddElementToEnd()
{
	int* id_temp = new int[size];
	std::string* name_temp = new std::string[size];
	int* count_temp = new int[size];
	double* price_temp = new double[size];

	for (int i = 0; i < size; i++)
	{
		id_temp[i] = id_arr[i];
		name_temp[i] = name_arr[i];
		count_temp[i] = count_arr[i];
		price_temp[i] = price_arr[i];
	}

	delete[]id_arr;
	delete[]name_arr;
	delete[]count_arr;
	delete[]price_arr;

	size++;
	id_arr = new int[size];
	name_arr = new std::string[size];
	count_arr = new int[size];
	price_arr = new double[size];

	for (int i = 0; i < size - 1; i++)
	{
		id_arr[i] = id_temp[i];
		name_arr[i] = name_temp[i];
		count_arr[i] = count_temp[i];
		price_arr[i] = price_temp[i];
	}


	id_arr[size - 1] = size - 1;
	std::cout << "\n������� ��� ������ ������: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, name_arr[size - 1], '\n');
	std::cout << "������� ���-�� ��� ����������: ";
	std::cin >> count_arr[size - 1];
	std::cout << "������� ���� ������: ";
	std::cin >> price_arr[size - 1];

	delete[]id_temp;
	delete[]name_temp;
	delete[]count_temp;
	delete[]price_temp;
}
void DeleteByIndex()
{
	int* id_temp = new int[size];
	std::string* name_temp = new std::string[size];
	int* count_temp = new int[size];
	double* price_temp = new double[size];

	for (int i = 0; i < size; i++)
	{
		id_temp[i] = id_arr[i];
		name_temp[i] = name_arr[i];
		count_temp[i] = count_arr[i];
		price_temp[i] = price_arr[i];
	}

	delete[]id_arr;
	delete[]name_arr;
	delete[]count_arr;
	delete[]price_arr;

	size--;
	id_arr = new int[size];
	name_arr = new std::string[size];
	count_arr = new int[size];
	price_arr = new double[size];
	int index;
	do
	{
		std::cout << "������� ID ������: ";
		std::cin >> index;
	} while (index < 0 || index > size);

	for (int i = 0, j = 0; i < size; i++, j++)
	{
		if (i != index)
		{
			id_arr[i] = id_temp[j];
			name_arr[i] = name_temp[j];
			count_arr[i] = count_temp[j];
			price_arr[i] = price_temp[j];
		}
		else
		{
			j++;
			id_arr[i] = id_temp[j];
			name_arr[i] = name_temp[j];
			count_arr[i] = count_temp[j];
			price_arr[i] = price_temp[j];
		}
	}

	delete[]id_temp;
	delete[]name_temp;
	delete[]count_temp;
	delete[]price_temp;
}

void DeleteMainArrays()	//@memery clear
{
	delete[]id_arr;
	delete[]name_arr;
	delete[]count_arr;
	delete[]price_arr;
	delete[]name_reciept;
	delete[]count_reciept;
	delete[]price_reciept;
}

void CashStatus()
{
	system("cls");
	std::cout << "�������� �������� ������\n\n";
	std::cout << "�������� � �����: " << cash << "\n������� �� ��������: " << cash_income << "\n������� �� �������: " << card_income << "\n\n�������� ������� �� �����: " << total_income << "\n\n";
	system("pause");
}

int TabCount(std::string* arr, int cur_size, std::string headliner)
{
	int t_res = 0;
	int longest = arr[0].length();

	for (int i = 1; i < cur_size; i++)
	{
		if (arr[i].length() > longest)
		{
			longest = arr[i].length();
		}
	}
	if (headliner.length() > longest)
	{
		longest = headliner.length();
	}
	for (int i = 0; i < longest / 8; i++)
	{
		t_res++;
	}
	if (longest % 8 != 0)
	{
		t_res++;
	}
	return t_res;
}
std::string TabSepparator(std::string str, int tab_len)
{
	std::string t_res = "";
	int negative = 8 * tab_len - str.length();
	for (int i = 0; i < negative / 8; i++)
	{
		t_res += "\t";
	}
	if (negative % 8 != 0)
	{
		t_res += "\t";
	}
	return t_res;
}


template<typename ArrayType>
void FillArray(ArrayType static_arr, ArrayType dyn_arr, int size)	//@static to dynamic data func
{

	for (int i = 0; i < size; i++)
	{
		dyn_arr[i] = static_arr[i];
	}

}
