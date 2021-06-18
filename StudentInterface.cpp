#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <mysql.h>

#include "cgicc/Cgicc.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTTPContentHeader.h"

using namespace std;
using namespace cgicc;

char sql[512];
char cgiOut[512];
vector<string> str={"Name: ","Student ID: ","Sex: ","Years: ","Class: ","Dept Name: ","Chinese: ","Math: ","English: ","Total Score: ","Credit: ","Ranking: "};

int main()
{
	
	try{
		
		Cgicc cgi;

      		// Send HTTP header
      		cout << HTTPContentHeader("text/html; charset=utf-8");
      		//cout << HTTPHTMLHeader() << endl;

      		// Set up the HTML document
      		cout << html() << head(title("Cgicc StudentInterface")) << endl;
      		cout << "<body background=\"../2.jpeg\">" << endl;

      		// Print out the submitted element
      		form_iterator student_id = cgi.getElement("student_id");
      		if(student_id != cgi.getElements().end()) {
      			cout << "Your student_id: " << **student_id << "<br>";
      		}
      		string student_id1((student_id)->getValue());
      		const char *student_id2 = student_id1.c_str();
      		
      		MYSQL mysql;
      		int res;
      		mysql_init(&mysql);
      		if(MYSQL *conn=mysql_real_connect(&mysql, "127.0.0.1","root","123456","Cgicc_StudentScoreSystem_Project",0,NULL,CLIENT_FOUND_ROWS)){
      			cout << "[+] Connection Success!" << "<br>";
      			
      			//sprintf(sql,"insert into LoginInfo values('%s','123456','sdt')",str2);
      			sprintf(sql,"select * from Infomation where student_id='%s'",student_id2);
      			res=mysql_query(conn,sql);
      			
      		        if(res){
      		           	cout<<"[-] Query Input Error!"<< "<br>";
      		           	cout<<"[-] Input Wrong Name Or Password!"<< "<br>";
      		        }
      			else{
				cout<<"[+] Query Input Success!"<< "<br>";
			}
      			
      			
      			MYSQL_ROW row;
      			auto rsl= mysql_store_result(conn);
      			unsigned int row_max_num = mysql_num_fields(rsl);
      			
      			while ((row = mysql_fetch_row(rsl)))
      			{	
      				
      				string row0=row[0];
      				string row1=row[1];
      				string row2=row[2];
      				
				if(student_id1 == row1){
					
					cout<<"<table border=\"1\" cellpadding=\"10\">";
      					cout<<"<tr>";
      					cout<<"<th>Name</th><th>Student ID</th><th>Sex</th><th>Years</th><th>Class</th><th>Dept Name</th>";
      					cout<<"<th>Chinese</th><th>Math</th><th>English</th><th>Score</th><th>Credit</th><th>Ranking</th>";
      					cout<<"</tr>";
      					cout<<"<tr>";
					
					for(int i = 0; i < row_max_num; i++){
						cout<<"<td>"<<row[i]<<"</td>"<<"<br>";
						
					}
					cout<<"</tr>";
					cout<< "</table>"<<"<br>";
					cout<<"[+] Search Success!"<<"<br>";
					
					
				}
				else cout<<"[-] Input Wrong Name Or Password!"<< "<br>";
			}
			
      			mysql_close(conn);
			mysql_close(&mysql);
			
		}
		else{
			cout << "connect failed" << endl;
		}
		
		
		// Close the HTML document
      		cout << body() << html();
      		

	}
	catch(exception& e) {
      	// handle any errors - omitted for brevity
   	}
}
