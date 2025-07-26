#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<tuple>
#include <cctype>
#include <sstream>
#include <map>
using namespace std;
namespace fs = std::filesystem;
void search_filter_type(ifstream& input_file, ofstream& output_file,string transaction,string keyword,string filter);
vector<pair<string, ifstream>> get_files(string path);
vector<pair<string, ifstream>> sort_files(vector<pair<string, ifstream>>& input);
void asc_sort_by_date(ofstream& main_file, ifstream& input_file);
void desc_sort_by_date(ofstream& main_file, ifstream& input_file);
void desc_sort_by_date(ofstream& output_file, ifstream& input_file);
void asc_sort_by_date(ofstream& output_file, ifstream& input_file);
void asc_sort_by_amount(ofstream& main_file, ifstream& input_file);
void desc_sort_by_amount(ofstream& main_file, ifstream& input_file);
tuple<string, string, string, string, string> parse_transaction(const string &line);
bool check_sub(string main,string s);
void search_without_filter(vector<string>input, ofstream& output_file,string keyword);
void search_by_type(vector<string>input, ofstream& output_file,string keyword,string filter);
void trim(string &s);
vector<string> merge_files(vector<pair<string, ifstream>>& input);
float sum(ifstream& input,string type);
float income_ratio(ifstream& input);
void persent_of_categorys(ifstream& input,ofstream& final,string type_transaction);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool check_name(string name)
{
	vector<string> months = {"January", "February", "March", "April", "May", "June",
	                         "July", "August", "September", "October", "November", "December"
	                        };
	for (int i = 0; i < 12; i++)
	{
		if (name == "transactions_" + months[i] + ".txt")
			return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
vector<pair<string, ifstream>> get_files(string path)
{
	vector<pair<string, ifstream>> myvec;
	for (const auto& file : fs::directory_iterator(path))
	{
		if (file.is_regular_file() && check_name(file.path().filename().string()))
		{
			ifstream fs(file.path());
			if (fs.is_open())
				myvec.push_back(make_pair(file.path().filename().string(), move(fs)));
		}
	}
	return myvec;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
vector<pair<string, ifstream>> sort_files(vector<pair<string, ifstream>>& input)
{
	vector<string> months = {"January", "February", "March", "April", "May", "June",
	                         "July", "August", "September", "October", "November", "December"
	                        };
	vector<pair<string, ifstream>> sorted_files;
	sorted_files.reserve(input.size());
	for (const auto& month : months)
	{
		for (int j = 0; j < input.size(); j++)
		{
			if (input[j].first == "transactions_" + month + ".txt")
			{
				sorted_files.push_back(move(input[j]));
			}
		}
	}
	return sorted_files;
}
//**********************************************************************************************************
void asc_sort_by_date(ofstream& main_file, ifstream& input_file,string filter)
{
	vector<pair<string, string>> myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string, string, string, string, string>parsed= parse_transaction(line);

		string date=(get<0>(parsed));
		if(filter=="")
		{
			myvec.push_back(make_pair(date,line));
		}
		else if(get<1>(parsed)==filter)
		{
			myvec.push_back(make_pair(date,line));
		}
	}
	sort(myvec.begin(),myvec.end());
	for (const auto& entry : myvec) {
		main_file << entry.second << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
void desc_sort_by_date(ofstream& output_file, ifstream& input_file,string filter) {
	vector<pair<string, string>> myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string, string, string, string, string>parsed= parse_transaction(line);

		string date=(get<0>(parsed));
		if(filter=="")
		{
			myvec.push_back(make_pair(date,line));
		}
		else if(get<1>(parsed)==filter)
		{
			myvec.push_back(make_pair(date,line));
		}
	}
	for (int i = myvec.size() - 1; i >= 0; i--) {
		output_file << myvec[i].second << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void asc_sort_by_category(ofstream& main_file, ifstream& input_file,string filter)
{
	vector<pair<string, string>>myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string,string,string,string,string>transaction=parse_transaction(line);
		if(filter=="")
		{
			myvec.push_back(make_pair(get<2>(transaction),line));
		}
		else if(get<1>(transaction)==filter)
		{
			myvec.push_back(make_pair(get<2>(transaction),line));
		}
	}
	sort(myvec.begin(),myvec.end());
	for (const auto& entry : myvec) {
		main_file << entry.second << endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void asc_sort_by_amount(ofstream& main_file, ifstream& input_file,string filter)
{
	vector<pair<double, string>>myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string,string,string,string,string>transaction=parse_transaction(line);
		double amount = stod(get<3>(transaction));
		if(filter=="")
		{
			myvec.push_back(make_pair(amount, line));
		}
		else if(get<1>(transaction)==filter)
		{
			myvec.push_back(make_pair(amount, line));
		}
	}
	sort(myvec.begin(),myvec.end());
	for (const auto& entry : myvec) {
		main_file << entry.second << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////
void desc_sort_by_category(ofstream& main_file, ifstream& input_file,string filter)
{
	vector<pair<string, string>>myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string,string,string,string,string>transaction=parse_transaction(line);
		if(filter=="")
		{
			myvec.push_back(make_pair(get<2>(transaction),line));
		}
		else if(get<1>(transaction)==filter)
		{
			myvec.push_back(make_pair(get<2>(transaction),line));
		}
	}
	sort(myvec.begin(),myvec.end());
	for (int i = myvec.size() - 1; i >= 0; i--) {
		main_file<< myvec[i].second << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////
void trim(string &s) {
	while (!s.empty() && isspace(s.front())) s.erase(s.begin());
	while (!s.empty() && isspace(s.back())) s.pop_back();
}
//////////////////////////////////////////////////////////////////////////////////////////
tuple<string, string, string, string, string> parse_transaction(const string &line)
{
	stringstream ss(line);
	string date, type, category, amount, description;
	getline(ss,date,'|');
	getline(ss,type,'|');
	getline(ss,category, '|');
	getline(ss,amount,'|');
	getline(ss,description);
	trim(date);
	trim(type);
	trim(category);
	trim(amount);
	trim(description);
	return make_tuple(date, type, category, amount, description);
}
///////////////////////////////////////////////////////////////////////////////////////

void desc_sort_by_amount(ofstream& main_file, ifstream& input_file,string filter)
{
	vector<pair<double, string>>myvec;
	string line;
	while (getline(input_file, line))
	{
		tuple<string,string,string,string,string>transaction=parse_transaction(line);
		double amount = stod(get<3>(transaction));
		if(filter=="")
		{
			myvec.push_back(make_pair(amount, line));
		}
		else if(get<1>(transaction)==filter)
		{
			myvec.push_back(make_pair(amount, line));
		}
	}
	sort(myvec.begin(),myvec.end());
	for (int i = myvec.size() - 1; i >= 0; i--) {
		main_file<< myvec[i].second << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////
bool check_sub(string main,string s)
{
	for (int i = 0; i < main.size(); i++) {
		main[i] = tolower(main[i]);
	}
	for (int i = 0; i < s.size(); i++) {
		s[i] = tolower(s[i]);
	}
	for(int i=0; i<main.size(); i++)
	{
		if(main[i]==s[0])
		{
			int count =0;
			for(int j=i; j<i+s.size(); j++)
			{
				if(main[j]==s[count])
				{
					count++;
				}
				else
				{
					break;
				}
			}
			if(count== s.size())
			{
				return true;
			}
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void search_without_filter(vector<string>input, ofstream& output_file,string keyword)
{
	int status=0;
	string line;
	for(int i=0; i<input.size(); i++)
	{
		tuple<string, string, string, string, string>parsed = parse_transaction(input[i]);
		if(check_sub(get<4>(parsed),keyword))
		{	status+=1;
			if(status==1)
			{	output_file<<"Transactions Found by the Keyword: "<<keyword<<endl;
				output_file<<"----------------------------------------"<<endl;
			}
			output_file<<input[i]<<endl;
		}
	}
	output_file<<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void search_by_type(vector<string>input, ofstream& output_file,string keyword,string filter)
{
	int status=0;
	string line;
	for(int i=0; i<input.size(); i++)
	{
		tuple<string, string, string, string, string>parsed = parse_transaction(input[i]);
		if(check_sub(get<4>(parsed),keyword)&&(get<1>(parsed)==filter))
		{	status+=1;
			if(status==1)
			{	output_file<<"Transactions Found by the Keyword: "<<keyword<<endl;
				output_file<<"----------------------------------------"<<endl;
			}
			output_file<<input[i]<<endl;
		}
	}
	output_file<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> merge_files(vector<pair<string, ifstream>>& input)
{
	vector<string> myvec;
	for(int i=0; i<input.size(); i++)
	{
		string line;
		while(getline(input[i].second,line))
		{
			myvec.push_back(line);
		}
	}
	return myvec;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
float sum(ifstream& input, string type)
{
	string line;
	float sum=0;
	while(getline(input,line))
	{
		tuple<string, string, string, string, string>parsed = parse_transaction(line);
		if(get<1>(parsed)==type)
		{
			float amount=stof(get<3>(parsed));
			sum=sum + amount;
		}
	}
	return sum;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
float income_ratio(ifstream& input)
{
	string line;
	float income=0;
	float expense=0;
	while(getline(input,line))
	{
		tuple<string, string, string, string, string>parsed = parse_transaction(line);
		if(get<1>(parsed)=="Income")
		{
			income =income +1;
		}
		if(get<1>(parsed)=="Expense")
		{
			expense=expense+1;
		}
	}
	return income/expense;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void persent_of_categorys(ifstream& input,ofstream& final,string type_transaction)
{
	float sum(ifstream& input, string type);
	string line;
	vector<pair<string, float>> income_categories;
	vector<pair<string, float>> expense_categories;
	float total_income = 0, total_expense = 0;
	float income= sum(input,"Income" );
	input.clear();
	input.seekg(0, ios::beg);
	float expense=sum(input,"Expense");
	input.clear();
	input.seekg(0, ios::beg);
	while (getline(input, line))
	{
		tuple<string, string, string, string, string> parsed = parse_transaction(line);
		string type = get<1>(parsed);
		string category = get<2>(parsed);
		float amount = stof(get<3>(parsed));
		if (type == "Income") {
			total_income += amount;
			bool found = false;
			for (auto &pair : income_categories) {
				if (pair.first == category) {
					pair.second += amount;
					found = true;
					break;
				}
			}
			if (!found) {
				income_categories.push_back({category, amount});
			}
		}
		else if (type == "Expense") {
			total_expense += amount;
			bool found = false;
			for (auto &pair : expense_categories) {
				if (pair.first == category) {
					pair.second += amount;
					found = true;
					break;
				}
			}
			if (!found) {
				expense_categories.push_back({category, amount});
			}
		}
	}
	if(type_transaction=="Expense")
	{
		final<<"Expense ratio breakdown:"<<endl;
		for(int i=0; i<expense_categories.size(); i++)
		{
			final<<"    - "<<expense_categories[i].first<<":"<<fixed << setprecision(2)<<expense_categories[i].second/expense*100<<"%"<<endl;
		}
	}
	if(type_transaction=="Income")
	{	final<<"Income ratio breakdown:"<<endl;
		for(int i=0; i<income_categories.size(); i++)
		{
			final<<"    - "<<income_categories[i].first<<":"<<fixed << setprecision(2)<<income_categories[i].second/income*100<<"%"<<endl;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void most_frequent_category(ifstream& input, ofstream& output, string type)
{
	map<string, int> category_count;
	string line;
	while (getline(input, line))
	{
		auto parsed = parse_transaction(line);
		if (get<1>(parsed) == type)
		{
			string category = get<2>(parsed);
			category_count[category]++;
		}
	}
	string most_common_category;
	int max_count = 0;
	for (const auto& entry : category_count)
	{
		if (entry.second > max_count)
		{
			max_count = entry.second;
			most_common_category = entry.first;
		}
	}
	if (type == "Income")
		output << "Most Frequent Income Category: " << most_common_category << " (" << max_count << " transactions)" << endl;
	else if (type == "Expense")
		output << "Most Frequent Expense Category: " << most_common_category << " (" << max_count << " transactions)" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void biggest_category_by_type(ifstream& input, ofstream& output, const string& type)
{
	map<string, float> category_map;
	string line;
	while (getline(input, line))
	{
		auto parsed = parse_transaction(line);
		if (get<1>(parsed) == type)
		{
			string category = get<2>(parsed);
			float amount = stof(get<3>(parsed));
			category_map[category] += amount;
		}
	}
	string max_category;
	float max_amount = 0;
	for (const auto& entry : category_map)
	{
		if (entry.second > max_amount)
		{
			max_amount = entry.second;
			max_category = entry.first;
		}
	}
	if (type == "Income")
		output << "Largest income category: " << max_category <<" ($" << max_amount <<")" << endl;
	else if (type == "Expense")
		output << "Largest expense category: " << max_category << " ($" << max_amount <<")"<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void top_3_transactions(ifstream& input, ofstream& output, const string& type)
{
	vector<pair<float, string>> transactions;
	string line;

	while (getline(input, line))
	{
		auto parsed = parse_transaction(line);
		if (get<1>(parsed) == type)
		{
			float amount = stof(get<3>(parsed));
			transactions.push_back({amount, line});
		}
	}
	sort(transactions.begin(), transactions.end(), [](auto& a, auto& b) {
		return a.first > b.first;
	});
	output << "Top 3 " << type << " Transactions:" << endl;
	for (int i = 0; i < min(3, (int)transactions.size()); ++i)
	{
		output <<"    "<<i+1<<". "<< transactions[i].second << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void report(ifstream& input,ofstream& final,string month)
{
	float total_income=sum(input,"Income");
	input.clear();
	input.seekg(0, ios::beg);
	float total_expense=sum(input,"Expense");
	input.clear();
	input.seekg(0, ios::beg);
	float ratio=income_ratio(input);
	input.clear();
	input.seekg(0, ios::beg);
	final<<"Monthly Financial Summary - "<<month<<" "<<2024<<endl;
	final<<"----------------------------------------"<<endl;
	final<<"Total income: $"<<total_income<<endl;
	final<<"Total spent: $"<<total_expense<<endl;
	final<<"Income to Expense Ratio: "<<fixed << setprecision(2)<<ratio<<endl;
	persent_of_categorys(input,final,"Income");
	input.clear();
	input.seekg(0, ios::beg);
	persent_of_categorys(input,final,"Expense");
	input.clear();
	input.seekg(0, ios::beg);
	biggest_category_by_type(input,final,"Income");
	input.clear();
	input.seekg(0, ios::beg);
	biggest_category_by_type(input,final,"Expense");
	input.clear();
	input.seekg(0, ios::beg);
	most_frequent_category(input,final,"Income");
	input.clear();
	input.seekg(0, ios::beg);
	most_frequent_category(input,final,"Expense");
	input.clear();
	input.seekg(0, ios::beg);
	top_3_transactions(input,final, "Income");
	input.clear();
	input.seekg(0, ios::beg);
	top_3_transactions(input,final, "Expense");
	input.clear();
	input.seekg(0, ios::beg);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void process_commands(ifstream& commands_file, const string& path) {
	string line;
	string filter_type;
	ofstream output("output/terminal_output.txt");
	while (getline(commands_file, line)) {
		stringstream ss(line);
		string command, month, field, order, keyword, filter;
		ss >> command;
		if (command == "SORT") {
			ss >> month >> field >> order;
			string filter_type;
			if (ss >> filter) {
				ss >> filter_type;
			}
			string filename = "transactions_" + month + ".txt";
			string full_path = path + "\\" + filename;
			ifstream input_file(full_path);
			if (field == "Date" && order == "ASC") {
				output<<"Ascending Sorted Transactions by Date"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if(filter=="FILTER")
				{
					asc_sort_by_date(output, input_file,filter_type);
				}
				else
				{
					asc_sort_by_date(output, input_file,"");
				}
			}
			else if (field == "Date" && order == "DESC") {
				output<<"Descending Sorted Transactions by Date"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if(filter=="FILTER")
				{
					desc_sort_by_date(output, input_file,filter_type);
				}
				else
				{
					desc_sort_by_date(output, input_file,"");
				}

			} else if (field == "Amount" && order == "ASC") {
				output<<"Ascending Sorted Transactions by Amount"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if (filter == "FILTER" && (filter_type == "Income" || filter_type == "Expense")) {
					asc_sort_by_amount(output, input_file,filter_type);
				} else {
					asc_sort_by_amount(output, input_file,"");
				}
			} else if (field == "Amount" && order == "DESC") {
				output<<"Descending Sorted Transactions by Amount"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if (filter == "FILTER" && (filter_type == "Income" || filter_type == "Expense")) {
					desc_sort_by_amount(output, input_file,filter_type);
				} else {
					desc_sort_by_amount(output, input_file,"");
				}
			} else if (field == "Category" && order == "ASC") {
				output<<"Ascending Sorted Transactions by Category"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if(filter=="FILTER")
				{
					asc_sort_by_category(output, input_file,filter_type);
				}
				else
				{
					asc_sort_by_category(output, input_file,"");
				}
			} else if (field == "Category" && order == "DESC") {
				output<<"Descending Sorted Transactions by Category"<<" - "<<month<<" 2024 "<<endl;
				output<<"----------------------------------------"<<endl;
				if(filter=="FILTER")
				{
					desc_sort_by_category(output, input_file,filter_type);
				}
				else
				{
					desc_sort_by_category(output, input_file,filter_type);
				}
			}
			input_file.close();
			output << endl;
		}
//------------------------------------------------------------------------------------
		else if (command == "SEARCH") {
			ss >> keyword;
			if (ss >> filter) {
				ss >> filter_type;
			}
			vector<pair<string, ifstream>> files = get_files(path);
			vector<pair<string, ifstream>> sorted_files=sort_files(files);
			vector<string>all_files=merge_files(sorted_files);
			if(filter=="FILTER")
			{
				search_by_type(all_files, output, keyword,filter_type);
			}
			else {

				search_without_filter(all_files, output, keyword);
			}
//------------------------------------------------------------------------------------------------------
		} else if (command == "SUMMARY") {
			ss >> month;
			string filename = "transactions_" + month + ".txt";
			string full_path = path + "\\" + filename;
			string summary="output/summary_logs/summary_"+month+".txt";
			ofstream summ(summary);
			ifstream input_file(full_path);
			report(input_file, summ, month);
			input_file.close();
		}
	}
	output.close();
}
////////////////////////////////////////////////////////////////////////////////////////
int main() {
	string path = "C:\\Users\\lenovo\\Desktop\\transactions_logs";
	ifstream commands("commands.txt");
	process_commands(commands, path);
	commands.close();
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
