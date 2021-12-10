// functions file
#include "Header1.h"


//function for user help and guidance for operating the program
void help()
{
	// listing down options for menu
	printf("\n1. add a new employee");
	printf("\n2. update information of an employee");
	printf("\n3. search for an employee");
	printf("\n4. show a list of all employees");
	printf("\n5. open help page");
	printf("\n6. quit program");
	menu();
}

//function for the main menu of the program
void menu()
{
	char menuChoiceEntered[30];
	int menuChoice;

	// requesting and verifying user input for menu
	printf("\n\n\nEnter choice for menu: ");
	scanf("%s",&menuChoiceEntered);
	if (((strlen(menuChoiceEntered)) == 1) && ((menuChoiceEntered[0] <= '6') && (menuChoiceEntered[0] >= '1')))
	{
		menuChoice = menuChoiceEntered[0] - '0';
		switch (menuChoice) 
		{
		case 1:
			assignEmployee();
			break;
		case 2:
			updateEmployee();
			break;
		case 3:
			searchEmployee();
			break;
		case 4:
			listEmployee();
			break;
		case 5:
			help();
			break;
		case 6:
			printf("\nThank you for using the program, and have a nice day! \n\n");
			exit();
		}
	}
	else
	{
		printf("wrong choice for menu, please try again.");
		menu();
	}
}

// function for adding a new employee
void assignEmployee()
{
	printf("\nadding a new employee");

	//creating employee structure
	struct employees
	{
		char name[30];
		char id[6];
		char telNum[5];
		char deptName[30];
	};

	struct employees newEmployee;
	int processSuccessful, noNumbers;

	// requesting and checking input for new employee's name
	do
	{
		processSuccessful = 0;
		printf("\nname of new employee: ");
		scanf("\n%[^\n]", &newEmployee.name);

		newEmployee.name[0] = toupper(newEmployee.name[0]);
		for (noNumbers = 0; noNumbers < strlen(newEmployee.name); noNumbers++)
		{
			if ((newEmployee.name[noNumbers] >= '0') && (newEmployee.name[noNumbers] <= '9'))
			{
				printf("input error, please try  again.");
				break;
			}
			else if (newEmployee.name[noNumbers] == ' ')
				newEmployee.name[noNumbers + 1] = toupper(newEmployee.name[noNumbers + 1]);
			if ((noNumbers + 1) == strlen(newEmployee.name))
			{
				processSuccessful = 1;
			}
		}
	} while (processSuccessful == 0);

	// requesting and checking input for new employee's id
	do
	{
		processSuccessful = 0;
		printf("\nID of new employee: ");
		scanf("%s", &newEmployee.id);

		if ((strlen(newEmployee.id) == 5) && ((newEmployee.id[0] == 'i') 
		|| (newEmployee.id[0] == 'I')) && ((newEmployee.id[1] == 'd') || (newEmployee.id[1] == 'D')) 
		&& ((newEmployee.id[2] >= '0') && (newEmployee.id[2] <= '9')) && ((newEmployee.id[3] >= '0') 
		&& (newEmployee.id[3] <= '9')) && ((newEmployee.id[4] >= '0') && (newEmployee.id[4] <= '9')))
		{
			newEmployee.id[0] = toupper(newEmployee.id[0]);
			newEmployee.id[1] = toupper(newEmployee.id[1]);
			processSuccessful = 1;
		}
		else
			printf("input error, please try  again.");
	} while (processSuccessful == 0);

	// requesting and checking input for new employee's extension number
	do
	{
		processSuccessful = 0;
		printf("\nextension number of new employee: ");
		scanf("%s", &newEmployee.telNum);

		if ((strlen(newEmployee.telNum) == 4) && ((newEmployee.telNum[0] >= '0') 
		&& (newEmployee.telNum[0] <= '9')) && ((newEmployee.telNum[1] >= '0') 
		&& (newEmployee.telNum[1] <= '9')) && ((newEmployee.telNum[2] >= '0') 
		&& (newEmployee.telNum[2] <= '9')) && ((newEmployee.telNum[3] >= '0') 
		&& (newEmployee.telNum[3] <= '9')))
		{
			processSuccessful = 1;
		}
		else
			printf("input error, please try  again.");
	} while (processSuccessful == 0);

	// requesting and checking input for new employee's department name
	int departmentNumber = 5, counter = 0, nameLength = 0;
	char departmentlist[5][30] = { "Admin", "Exam", "Finance", "Marketing", "Visa" };
	do
	{
		processSuccessful = 0;
		printf("\ndepartment name of new employee: ");
		scanf("\n%[^\n]", &newEmployee.deptName);
		newEmployee.deptName[0] = toupper(newEmployee.deptName[0]);

		for (int counter = 0; counter < departmentNumber; counter++)
		{
			if ( (strstr(newEmployee.deptName, departmentlist[counter]) != NULL) 
			&& (strstr(newEmployee.deptName, "department") || (strstr(newEmployee.deptName, "Department"))) )
			{
				for (nameLength = 0; nameLength < strlen(newEmployee.deptName); nameLength++)
				{
					if (newEmployee.deptName[nameLength] == ' ')
						newEmployee.deptName[nameLength + 1] = toupper(newEmployee.deptName[nameLength + 1]);
				}
				processSuccessful = 1;
			}
		}	
		if (processSuccessful == 0)
			printf("input error, please try  again.");
	} while (processSuccessful == 0);
	printf("\nnew employee info: \n%s\t%s\t%s\t%s\n", newEmployee.name, newEmployee.id, newEmployee.telNum, newEmployee.deptName);

	FILE* file;
	file = fopen("tel.txt", "r");

	if (file == NULL)
	{	
		// if no file found, creating a tel.txt file and adding first employee's data
		printf("\nNo file found, creating new txt file.");
		printf("\nnew employee data created\n");
		file = fopen("tel.txt", "a");
		fprintf(file, "%s\t%s\t%s\t%s", newEmployee.name, newEmployee.id, newEmployee.telNum, newEmployee.deptName);
		fclose(file);
	}
	else
	{
		struct employees fileEmployee[50];
		int recordCheck = 0, processImpossible = 0; 
		processSuccessful = 0;

		// checking for any duplicate records
		while ((!feof(file)) && processSuccessful == 0)
		{
			fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &fileEmployee[recordCheck].name, &fileEmployee[recordCheck].id, &fileEmployee[recordCheck].telNum, &fileEmployee[recordCheck].deptName);
			if (((strcmp(fileEmployee[recordCheck].name, newEmployee.name)) == 0)) 
			{
				printf("\nexisitng employee with same name found:\n%s\t%s\t%s\t%s\n", fileEmployee[recordCheck].name, fileEmployee[recordCheck].id, fileEmployee[recordCheck].telNum, fileEmployee[recordCheck].deptName);
				processSuccessful++;
			}
			else if (((strcmp(fileEmployee[recordCheck].id, newEmployee.id)) == 0) || ((strcmp(fileEmployee[recordCheck].telNum, newEmployee.telNum)) == 0))
			{
				printf("\nexisitng employee with similar data found:\n%s\t%s\t%s\t%s\n", fileEmployee[recordCheck].name, fileEmployee[recordCheck].id, fileEmployee[recordCheck].telNum, fileEmployee[recordCheck].deptName);
				processImpossible++;
				processSuccessful++;
			}
			else
				recordCheck++;
		}
		fclose(file);

		// adding the new employee data to existing record file if no errors detected
		if (processImpossible == 0)
		{
			if (processSuccessful == 0)
			{
				printf("\nnew employee data created\n");
				file = fopen("tel.txt", "a");
				fprintf(file, "\n%s\t%s\t%s\t%s", newEmployee.name, newEmployee.id, newEmployee.telNum, newEmployee.deptName);
				fclose(file);
			}
			else
			{
				char userInput[30];
				do
				{
					//informing user regarding the duplication of names in the record file
					printf("\nWould you like to add the new employee that has the same name as an existing record ?\n 1. Yes\n 2. No\nInput: ");
					scanf("%s", userInput);
					if ((strlen(userInput) == 1) && (userInput[0] == '1'))
					{
							printf("\nnew employee data created\n");
							file = fopen("tel.txt", "a");
							fprintf(file, "\n%s\t%s\t%s\t%s", newEmployee.name, newEmployee.id, newEmployee.telNum, newEmployee.deptName);
							fclose(file);
							processSuccessful = 0;
					}
					else if ((strlen(userInput) == 1) && (userInput[0] <= '2'))
					{
						printf("\nNew employee record creation cancelled.");
						break;
					}
					else
						printf("\nInvalid input, please try again.");
				} while (processSuccessful != 0);
			}
		}
		else
		{
			printf("\nCan not add new employee record.");
		}
	}
	menu();
}

// function for updating the number of an employee
void updateEmployee()
{
	printf("\nupdating employee information");

	//creating employee structure
	struct employees
	{
		char name[30];
		char id[6];
		char telNum[5];
		char deptName[30];
	};

	//opening and verifying employee records file
	FILE* file;
	file = fopen("tel.txt", "r");
	if (file == NULL) 
	{
		printf("\nCould not find an existing file, create one by adding an employee.");
		menu();
	}
	struct employees fileEmployee[50];
	int i = 0, processSuccessful = 0, InputIsName = 0;
	char newTelNumber[5];

	//requesting search key
	char searchInfo[50] = "no name or id";
	printf("\nenter the employee's full name or ID: ");
	scanf("\n%[^\n]", searchInfo);

	// correcting case of the search key inputted by the user
	if ((strlen(searchInfo) == 5) && ((searchInfo[0] == 'i') || (searchInfo[0] == 'I')) 
	&& ((searchInfo[1] == 'd') || (searchInfo[1] == 'D'))
	&& ((searchInfo[2] >= '0') && (searchInfo[2] <= '9')))
	{
		searchInfo[0] = toupper(searchInfo[0]);
		searchInfo[1] = toupper(searchInfo[1]);
	}
	else
	{
		InputIsName++;
		searchInfo[0] = toupper(searchInfo[0]);
		int firstWordCapital = 0;
		for (firstWordCapital = 0; firstWordCapital < strlen(searchInfo); firstWordCapital++)
		{
			if (searchInfo[firstWordCapital] == ' ')
				searchInfo[firstWordCapital + 1] = toupper(searchInfo[firstWordCapital + 1]);
		}
	}
	printf("searching %s...\n", searchInfo);

	//scannign through file to find any matches or errors
	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &fileEmployee[i].name, &fileEmployee[i].id, &fileEmployee[i].telNum, &fileEmployee[i].deptName);
		//identifying matches
		if (((strcmp(searchInfo, fileEmployee[i].name)) == 0) || ((strcmp(searchInfo, fileEmployee[i].id)) == 0))
		{
			if ((strcmp(searchInfo, fileEmployee[i].name)) == 0)
				InputIsName++;
			if (InputIsName >= 3)
			{
				//informing user if multiple records related to search key found
				printf("\nmultiple employees with the same name found.");
				InputIsName++;
			}
			printf("\ncurrent employee data: \n%s\t%s\t%s\t%s", fileEmployee[i].name, fileEmployee[i].id, fileEmployee[i].telNum, fileEmployee[i].deptName);
			do
			{
				//requesting for new telephone number for the matching record
				processSuccessful = 0;
				printf("\nenter employee's new phone number: ");
				scanf("%s", newTelNumber);
				//checking input validity
				if ((strlen(newTelNumber) == 4) && ((newTelNumber[0] >= '0') && (newTelNumber[0] <= '9')) 
				&& ((newTelNumber[1] >= '0') && (newTelNumber[1] <= '9')) && ((newTelNumber[2] >= '0')
					&& (newTelNumber[2] <= '9')) && ((newTelNumber[3] >= '0') && (newTelNumber[3] <= '9')))
				{
					strcpy(fileEmployee[i].telNum, newTelNumber);
					processSuccessful = 1;
				}
				else
				{
					printf("\ninput error, please enter the new extension number again.");
				}
			} while (processSuccessful == 0);
		}
		i++;
	}
	fclose(file);

	// updating records if no errors found
	if (processSuccessful == 1)
	{
		file = fopen("tel.txt", "w");
		int printingFile;
		for (printingFile = 0; printingFile < i; printingFile++)
		{
			if ((printingFile + 1) == i)
			{
				fprintf(file, "%s\t%s\t%s\t%s", fileEmployee[printingFile].name, fileEmployee[printingFile].id, fileEmployee[printingFile].telNum, fileEmployee[printingFile].deptName);
				printf("\nemployee's number has been updated");
				break;
			}
			fprintf(file, "%s\t%s\t%s\t%s\n", fileEmployee[printingFile].name, fileEmployee[printingFile].id, fileEmployee[printingFile].telNum, fileEmployee[printingFile].deptName);
		}
		fclose(file);
	}
	else
		printf("no employee with that information found.");
	menu();
}

// function for searching employees' records using a search key
void searchEmployee()
{
	printf("\nsearching employee");

	//creating employee structure
	struct employees
	{
		char name[30];
		char id[6];
		char telNum[5];
		char deptName[30];
	};

	//opening and verifying employee records file
	FILE* file;
	file = fopen("tel.txt", "r");
	if (file == NULL) 
	{
		printf("\nCould not find an existing file, create one by adding an employee.");
		menu();
	}
	struct employees fileEmployee[50];
	int i = 0, processSuccessful=0;

	//requesting for search key
	char searchInfo[50] = "empty";
	printf("\nenter the searching employee's full name or ID: ");
	scanf("\n%[^\n]",searchInfo);	//using scanf instead of gets due to \n being in buffer

	// correcting case of the search key inputted by the user
	if ((strlen(searchInfo) == 5) && ((searchInfo[0] == 'i') || (searchInfo[0] == 'I')) 
	&& ((searchInfo[1] == 'd') || (searchInfo[1] == 'D')) && ((searchInfo[2] >= '0') 
	&& (searchInfo[2] <= '9')))
	{
		searchInfo[0] = toupper(searchInfo[0]);
		searchInfo[1] = toupper(searchInfo[1]);
	}
	else
	{
		searchInfo[0] = toupper(searchInfo[0]);
		int firstWordCapital = 0;
		for (firstWordCapital = 0; firstWordCapital < strlen(searchInfo); firstWordCapital++)
		{
			if (searchInfo[firstWordCapital] == ' ')
				searchInfo[firstWordCapital + 1] = toupper(searchInfo[firstWordCapital + 1]);
		}
	}
	printf("searching %s...\n", searchInfo);

	//scanning file and comparing with search key
	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &fileEmployee[i].name, &fileEmployee[i].id, &fileEmployee[i].telNum, &fileEmployee[i].deptName);
		//identifying matches
		if (((strcmp(searchInfo, fileEmployee[i].name)) == 0) || ((strcmp(searchInfo, fileEmployee[i].id)) == 0))
		{
			printf("\nEmployee found.");
			printf("\n%s\t%s\t%s\t%s\n", fileEmployee[i].name, fileEmployee[i].id, fileEmployee[i].telNum, fileEmployee[i].deptName);
			processSuccessful++;
			i++;
		}
	}
	// reporting if no matches for user input found
	if (processSuccessful == 0)
	{
		printf("\nno employee found.\n");
	}
	fclose(file);
	menu();
}

// function for listing all employees in the system
void listEmployee()
{
	printf("\nlisting all employees\n");

	//creating employee structure
	struct employees
	{
		char name[30];
		char id[6];
		char telNum[5];
		char deptName[30];
	};

	//opening and verifying employee records file
	FILE* file;
	file = fopen("tel.txt", "r");
	if (file == NULL) {

		printf("Could not find an existing file, create one by adding an employee.");
		menu();
	}
	struct employees fileEmployee[50];
	int i = 0;

	//scannign file
	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &fileEmployee[i].name, &fileEmployee[i].id, &fileEmployee[i].telNum, &fileEmployee[i].deptName);
		i++;
	}

	int fileTotalRecords = i;
	//i equals the total employee records scanned

	int departmentNumber = 5, counter1 = 0, counter2 = 0;
	char departmentlist[5][30] = { "Admin", "Exam", "Finance", "Marketing", "Visa" };
	//departmentlist is array of all the departments sorted alphabetically
		
	for (int counter1 = 0; counter1 < departmentNumber; counter1++)
	//going through each department alphabetically
	{
		for (int counter2 = 0; counter2 < fileTotalRecords; counter2++)
		//going through each employee record
		{
			if (strstr(fileEmployee[counter2].deptName, departmentlist[counter1]) != NULL)
			//printing employee record if matching with department name
			{
				printf("\n%s\t%s\t%s\t%s\n", fileEmployee[counter2].name, fileEmployee[counter2].id, fileEmployee[counter2].telNum, fileEmployee[counter2].deptName);
			}
		}
	}
	fclose(file);
	menu();
}