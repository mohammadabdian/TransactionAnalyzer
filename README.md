# TransactionAnalyzer

A C++ tool for analyzing and summarizing personal financial transactions.

## Features

- Sort by **Date**, **Amount**, or **Category**
- Filter by **Income** or **Expense**
- Search keywords in descriptions
- Generate monthly reports:
  - Total income/expenses
  - Category breakdown
  - Most frequent & largest categories
  - Top 3 transactions

## File Structure

- `Transaction_analyzer.cpp` – main source file  
- `commands.txt` – commands to execute  
- `transactions/` – input files like `transactions_January.txt`  
- `output/` – results and reports

## How it Works

- Reads transaction files from `transactions/`
- Executes commands from `commands.txt`
- Outputs results in `output/` and summaries in `output/summary_logs/`


