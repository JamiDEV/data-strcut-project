#include <iostream>
#include <string>
#include <fstream>
#include <cctype>


using std::cout;
using std::cin;


void parseFile();

void inputDataToFile();

struct srcTree 
{
	int productNum;
	std::string productName;
	std::string productVer;
	std::string productPrice;
	srcTree* left;
	srcTree* right;
	srcTree* parent;
};

srcTree* grabLastestNode(int productNum, std::string productName, std::string productVer, std::string productPrice)
{
	srcTree*  lastestNode = new  srcTree();
	lastestNode->productNum = productNum;
	lastestNode->productName = productName;
	lastestNode->productVer = productVer;
	lastestNode->productPrice = productPrice;
	lastestNode->left = NULL;
	lastestNode->right = NULL;
	lastestNode->left = NULL;
	lastestNode->parent = NULL;
	return lastestNode;
}

srcTree* inject(srcTree* rootPtr, int productNum, std::string productName, std::string productVer, std::string productPrice)
{
	static srcTree *p;
	srcTree *aNode;
	
	if ( rootPtr == NULL)
	{
		aNode = grabLastestNode(productNum, productName, productVer, productPrice);
		aNode->parent = p;
		return aNode;
	}
	if ( productNum <= rootPtr-> productNum)
	{
		p = rootPtr;
		rootPtr->left = inject(rootPtr->left, productNum, productName, productVer, productPrice);
	}
	else
	{
		p = rootPtr;
		rootPtr->left = inject(rootPtr->left, productNum, productName, productVer, productPrice);
	}
	return rootPtr;
}

srcTree* rootPtr = NULL;

bool seek(srcTree* rootPtr, int productNum)
{
	if (rootPtr == NULL)
	{
		return false;		
	}
	else if (rootPtr->productNum == productNum)
	{
		return true;	
	}
	else if (productNum <= rootPtr->productNum)
	{
		return seek(rootPtr->left, productNum);
	}
	else
	{
		return seek(rootPtr->right, productNum);
	}
}

struct srcTree* Remove(struct srcTree *rootPtr, int productNum)
{
	if (rootPtr == NULL)
	{
		return rootPtr;
	}
	
	else if (productNum < rootPtr-> productNum)
		rootPtr->left = Remove(rootPtr->left, productNum);
	else if (productNum < rootPtr-> productNum)
		rootPtr->right = Remove(rootPtr->right, productNum);
	else
	{
		if (rootPtr->left == NULL && rootPtr->right == NULL) /* no children */
		{
			delete rootPtr;
			rootPtr = NULL;
		}
		else if(rootPtr->left == NULL) /*one child */
		{
			struct srcTree *temp = rootPtr;
			rootPtr = rootPtr->right;
			delete temp;
		}
		else if (rootPtr->right == NULL)
		{
			struct srcTree *temp = rootPtr;
			rootPtr = rootPtr->left;
			delete temp;
		}
	}
	return rootPtr;
}


int main()
{

	std::ofstream appFile;
	appFile.open("software.txt");
	appFile << "12\nPhotoshop\nCS5\n500\n";
	appFile << "22\nOffice\n2010\n150\n";
	appFile << "34\nVisualStudio\n2010\n600\n";
	appFile.close();
	parseFile();
	bool breakLoop = false;
	char dataInput;
	
	try{
			while (breakLoop == false)
	{
		std::cout << "******************************" << std::endl;
		std::cout << "      APP DATABASE SYSTEM   " << std::endl ;
		std::cout << "******************************" << std::endl;
		std::cout <<"(A)      Load New App Package    \n" << std::endl;
		std::cout <<"(B)      Remove Purchased App Packages \n"<< std::endl;
		std::cout <<"(C)      Search for App Package \n"<< std::endl;
		std::cout <<"(X)      Exit Database \n "  << std::endl;
		std::cin >> dataInput;
		system("CLS");
		
		switch (toupper(dataInput))
		{
		case 'A':
			inputDataToFile();
			parseFile();
			break;
		case 'B':
			char removeApp;
			std::cout << "Enter app package # to be removed : " << std::endl;
			std::cin >>removeApp;
			system("CLS");
			
			rootPtr = Remove(rootPtr, removeApp);
			
			std::cout << "App package # " << removeApp << " has been removed" << std::endl;
			system ("PAUSE");
			break;
		case 'C':
			int productNum;
			std::cout << "Enter app package # :" << std::endl;
			std::cin >> productNum; 
			system("CLS");
			
			if (seek(rootPtr, productNum)== true)
			{
				std::cout << "App package #" << productNum << " is in the database" << std::endl;
				system("PAUSE");
				system("CLS");
			}
			else
			{
				std::cout << "App package #" << productNum << " is not in database" << std::endl;
				system("PAUSE");
				system("CLS");
			}
			break;
		case 'X':
			std::cout<< " have a nice day" << std::endl;
			exit(0);
			break;
		default:
			std::cout << "invalid choice" << std::endl;
			system("PAUSE");
			system("CLS");
			break;
			
		}
				
	}
	}
	catch(...)
	{
		std:: cout << "OOPS!...Something went wrong :(" << std::endl;
	}


 return 0;	
}

//FUNCTIO BUILDOUTS// 
void parseFile()
{
	std::string parseName, parseVersion, parsePrice;
	int parseCode;
	std::ifstream appFile("software.txt");
	if (appFile.is_open())
	{
		while (appFile >> parseCode >> parseName >> parseVersion >> parsePrice)
		{
			rootPtr = inject(rootPtr, parseCode, parseName, parseVersion, parsePrice);
		}
		appFile.close();
	}
	else
	{
		std::cout << "File could not be loaded" << std::endl;
		system("PAUSE");
		system("CLS");
	}
}

void inputDataToFile()
{
	std::ofstream appFile("software.txt", std::ios::app);
	std::string userCapture;
	if (appFile.is_open())
	{
		std::cout << "Enter in app package #: " << std::endl;
		std::cin >> userCapture;
		appFile << userCapture << std::endl;
		system("CLS");
		
		std::cout << "Enter in app name: " << std::endl;
		std::cin >> userCapture;
		
		int i, j = 0;
		for ( i = 0; userCapture[i] != '\0' ; ++i)
		{
			if( userCapture[i] != ' ')
				userCapture[j++] = userCapture[i];
		}
		userCapture[j] = '\0';
		
		appFile << userCapture << std::endl;
		system("CLS");
		
		appFile.close();	
	}
	else
	{
		std::cout << "File could not be loaded" << std::endl;
		system("PAUSE");
		system("CLS");
	}
}
