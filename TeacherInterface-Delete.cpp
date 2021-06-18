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

int main()
{
	
	try{
		
		Cgicc cgi;

      		// Send HTTP header
      		cout << HTTPContentHeader("text/html; charset=utf-8");
      		//cout << HTTPHTMLHeader() << endl;

      		// Set up the HTML document
      		cout << html() << head(title("Cgicc Login")) << endl;
      		cout << "<body background=\"../2.jpeg\">" << endl;

      		// Print out the submitted element
      		form_iterator delete_type = cgi.getElement("delete_type");
      		if(delete_type != cgi.getElements().end()) {
      			cout << "Your delete_type: " << **delete_type << "<br>";
      		}
      		form_iterator delete_data = cgi.getElement("delete_data");
      		if(delete_data != cgi.getElements().end()) {
      			cout << "Your delete_data: " << **delete_data << "<br>";
      		}
      		
      		
      		string delete_type1((delete_type)->getValue());
      		const char *delete_type2 = delete_type1.c_str();
      		string delete_data1((delete_data)->getValue());
      		const char *delete_data2 = delete_data1.c_str();
      		
      		MYSQL mysql;
      		int res;
      		mysql_init(&mysql);
      		if(MYSQL *conn=mysql_real_connect(&mysql, "127.0.0.1","root","123456","Cgicc_StudentScoreSystem_Project",0,NULL,CLIENT_FOUND_ROWS)){
      			cout << "[+] Connection Success!\n" << "<br>";
      			
      			string a="name",b="student_id",c="dept_name",d="class";
      			const char *a1=a.c_str(),*b1=b.c_str(),*c1=c.c_str();
      			
      			sprintf(sql,"delete from Infomation where %s=%s",delete_type2,delete_data2);
      			//sprintf(sql,"select * from Infomation where student_id='%s'",student_id2);
      			cout<<sql<<"<br>";
      			res=mysql_query(conn,sql);
      			
      		        if(res){
      		           	cout<<"[-] Query Input Error!"<< "<br>";
      		        }
      			else{
				cout<<"[+] Query Input Success!"<< "<br>";
			}
      			
      			sprintf(sql,"select * from Infomation");
      			res=mysql_query(conn,sql);
      			if(!res)cout<<"[+] Query Input2 Success!"<< "<br>";
      			MYSQL_ROW row;
      			auto rsl= mysql_store_result(conn);
      			unsigned int row_max_num = mysql_num_fields(rsl);
      			
      			cout<<"<table border=\"1\" cellpadding=\"10\">";
      			cout<<"<tr>";
      			cout<<"<th>Name</th><th>Student ID</th><th>Sex</th><th>Years</th><th>Class</th><th>Dept Name</th>";
      			cout<<"<th>Chinese</th><th>Math</th><th>English</th><th>Score</th><th>Credit</th><th>Ranking</th>";
      			cout<<"</tr>";
      			
      			
      			while ((row = mysql_fetch_row(rsl)))
      			{	
      				cout<<"<tr>";
				for(int i = 0; i < row_max_num; i++){
					cout<<"<td>"<<row[i]<<"</td>"<<"<br>";	
				}
				cout<<"</tr>";
			}
			cout<< "</table>"<<"<br>";
			
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
