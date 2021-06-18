char cmd[500] = {};
char dbuser[30] = "root";
char dbpasswd[30] = "123456";
char dbip[30] = "localhost";
char dbname[50]= "Local instance 3306";
char* query = NULL;

class Connection {
	public:
		 void init(){
			MYSQL *connect; // Create a pointer to the MySQL instance
			connect=mysql_init(connect); // Initialise the instance
			
			/* This If s irrelevant and you don't need to show it. I kept it in for Fault Testing.*/
			if(!connect)    /* If instance didn't initialize say so and exit with fault.*/
			{
				cout << "MySQL Initialization Failed";
				
			}
			
			/* Now we will actually connect to the specific database.*/
			connect=mysql_real_connect(connect,dbip,dbuser,dbpasswd,dbname,0,NULL,0);
			
			/* Following if statements are unneeded too, but it's worth it to show on your
			first app, so that if your database is empty or the query didn't return anything it
			will at least let you know that the connection to the mysql server was established. */
			cout << "[+] Exchange Order Book v1.0\n";
			cout << "[+] Attempting connection to database\n";
			if(connect){
				cout << "[+] Connection Success!\n";
				cout << "[+] Loading initializationn\n";
			}
			else{
				cout << "[!] Connection Failed!\n";
				
			}
			
			MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
			MYSQL_ROW row;  /* Assign variable for rows. */
			// mysql_query(connect,"SELECT * FROM orderque");
			/* Send a query to the database. */
			unsigned int i = 1; /* Create a counter for the rows */
	
		}
};
