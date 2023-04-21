#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void resetProgram()
{

}

int main()
{
	string name = " ";
	int numMonths = 0;
	double totalTXU = 0;
	double currentTXU = 0;
	double totalTDU = 0;
	double currentTDU = 0;
	int monthlyKWH[12];
	char earlyCancellationFeeChar = ' ';

	int TDUName = 0;
	double TDUChargesPerMonth = 0;
	double TDUChargesPerKWH = 0;

	while (true)
	{
		//Prompts the user for the name of the bill
		cout << "What is the name for the bill? : ";

		//Performs getline and outputs to name
		getline(cin, name);

		//Promts the user for the number of months the data will be collected
		cout << endl << "How many months of data will be entered? (1-12): ";
		//Outputs to numMonths
		cin >> numMonths;

		while (numMonths < 1 || numMonths > 12 || cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a number between 1-12! : ";
			cin >> numMonths;
			cout << endl;
		}

		if (numMonths < 12)
		{
			while (true)
			{
				//Prompt user if they want to cancel their service
				cout << endl << "Do you want to cancel our service? (y/n): ";

				//Outputs the char entered into earlyCancellationFeeChar
				cin >> earlyCancellationFeeChar;

				//If earlyCancellationFeeChar == 'y' then add the Early Cancellation Fee to the TXU charge
				if (earlyCancellationFeeChar == 'y')
				{
					cout << endl << "(NOTICE : Early Cancellation Fee ($150) will apply!)" << endl;
					totalTXU += 150;
					break;
				}
				else if (earlyCancellationFeeChar == 'n')
				{
					break;
				}
				else
				{
					continue;
				}
			}
		}

		//Prompts user for the TDU name
		cout << endl << "(ONCOR = 1)" << endl << "(CENTERPOINT ENERGY = 2)" << endl << "(AEP TEXAS CENTERAL = 3)" << endl << "(APE TEXAS NORTH = 4)" << endl << "(TEXAS - NEW MEXICO POWER = 5)" << endl << "What TDU are you currently using? : ";

		//Performs getline and outputs to TDUName
		//If error flag appears then call reset program
		cin >> TDUName;

		while (TDUName < 1 || TDUName > 5 || cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a number between 1-5! : ";
			cin >> TDUName;
			cout << endl;
		}

		switch (TDUName)
		{
		case 1:
			TDUChargesPerMonth = 3.42;
			TDUChargesPerKWH = 0.038447;
			break;
		case 2:
			TDUChargesPerMonth = 5.47;
			TDUChargesPerKWH = 0.040312;
			break;
		case 3:
			TDUChargesPerMonth = 9;
			TDUChargesPerKWH = 0.04846;
			break;
		case 4:
			TDUChargesPerMonth = 10.53;
			TDUChargesPerKWH = 0.040199;
			break;
		case 5:
			TDUChargesPerMonth = 7.85;
			TDUChargesPerKWH = 0.048321;
			break;
		}

		for (int i = 0; i < numMonths; i++)
		{
			cout << endl << "Enter the kWH for month " << i + 1 << " : ";

			cin >> monthlyKWH[i];

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Please enter a number! : ";
				cin >> monthlyKWH[i];
				cout << endl;
			}
		}

		//Reciept

		cout << setprecision(2) << fixed;
		cout << endl << "Name : " << name << endl;

		for (int i = 0; i < numMonths; i++)
		{
			//Calculate the current TXU
			cout << "Month " << i + 1 << " : " << endl;
			if (monthlyKWH[i] >= 0 && monthlyKWH[i] <= 1200)
			{
				currentTXU = monthlyKWH[i] * 0.073 + 9.95;
			}
			else if (monthlyKWH[i] > 1200 && monthlyKWH[i] <= 2000)
			{
				currentTXU = (1200 * 0.073) + (monthlyKWH[i] - 1200) * 0.037 + (9.95 - 15);
			}
			else if (monthlyKWH[i] > 2000)
			{
				currentTXU = (1200 * 0.073) + (800 * 0.037) + (monthlyKWH[i] - 2000) * 0.077 + (9.95 - 15);
			}

			//Calculate the current TDU
			currentTDU = monthlyKWH[i] * TDUChargesPerKWH + TDUChargesPerMonth;

			cout << "TXU Monthly Cost : " << currentTXU << endl;
			cout << "TDU Monthly Cost : " << currentTDU << endl;
			cout << "Total Monthly Cost : " << currentTXU + currentTDU << endl << endl;

			totalTXU += currentTXU;
			totalTDU += currentTDU;
		}

		cout << "Total TXU : " << totalTXU << endl;
		cout << "Total TDU : " << totalTDU << endl;
		cout << "Total Cost : " << totalTXU + totalTDU << endl << endl << endl;

		cout << "Enter data again for another bill calculculation!" << endl;

		cin.clear();
		cin.ignore(100000, '\n');
	}
}
