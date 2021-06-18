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
      		form_iterator student_id = cgi.getElement("student_id");
      		if(student_id != cgi.getElements().end()) {
      			cout << "Your student_id: " << **student_id << "<br>";
      		}
      		form_iterator passwd = cgi.getElement("password");
      		if(passwd != cgi.getElements().end()) {
         		cout << "Your password: " << **passwd << "<br>";
      		}
		form_iterator psn_type = cgi.getElement("persontype");
      		if(psn_type != cgi.getElements().end()) {
         		cout << "Your person-type: " << **psn_type << "<br>";
      		}
      		
      		string student_id1((student_id)->getValue());
      		const char *student_id2 = student_id1.c_str();
      			
      		string passwd1((passwd)->getValue());
      		//const char *passwd2 = passwd1.c_str();
      		
      		string psn_type1((psn_type)->getValue());
      		//const char *psn_type2 = psn_type1.c_str();
      		
      		MYSQL mysql;
      		int res;
      		mysql_init(&mysql);
      		if(MYSQL *conn=mysql_real_connect(&mysql, "127.0.0.1","root","123456","Cgicc_StudentScoreSystem_Project",0,NULL,CLIENT_FOUND_ROWS)){
      			cout << "[+] Connection Success!\n" << "<br>";
      			
      			//sprintf(sql,"insert into LoginInfo values('%s','123456','sdt')",str2);
      			sprintf(sql,"select * from LoginInfo where student_id='%s'",student_id2);
      			res=mysql_query(conn,sql);
      			
      		        if(res){
      		           	cout<<"[-] Query Input Error!"<< "<br>";
      		           	cout<<"[-] Input Wrong Student_ID Or Password!"<< "<br>";
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
      				
				if(student_id1 == row0){
					if(passwd1 == row1){
						if(psn_type1 == row2){
							for(int i = 0; i < row_max_num; i++){
								cout<<row[i]<<"<br>";
							}
							cout<<"[+] Search Success!"<<"<br>";
							
							string student="sdt";
							string teacher="tcr";
							
							if(psn_type1 == student){
								sprintf(sql,"<a href=\"./StudentInterface.cgi?student_id=%s\" rel=\"external\" title=\"nothing\"> StudentInterface </a>",student_id2);
								cout<<sql;
								
							}
							else if(psn_type1 == teacher){
								cout<< "<a href=\"../TeacherInterface-Function.html\" rel=\"external\" title=\"nothing\">"
								<<" TeacherFunctionInterface </a>";
							}
							else
								cout<<"[-]Could Not Find Correct Person Type!";
							
						}
						else cout<<"[-] Input Wrong Name Or Password!"<< "<br>";
					}
					else cout<<"[-] Input Wrong Name Or Password!"<< "<br>";
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
      		cout << "</body>" << html();
      		

	}
	catch(exception& e) {
      	// handle any errors - omitted for brevity
   	}
}
