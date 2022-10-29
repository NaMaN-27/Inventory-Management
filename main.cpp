
#include<windows.h>
#include<mysql.h>

#include<iostream>
#include<fstream>



using namespace std;
int qstate, previousQuantity = 0;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_ROW row1;
MYSQL_RES* res;
MYSQL_RES* res1;
const char* password="";


class project
{
public:
    project();
    void menu();
    void util();
    void show();
    void soldItems();
    void addNewItem();
    void editItem();
    void deleteItem();
    void addNewSale();
    void reportmenu();
    void report(int);
    void pL(int);
    void individual_report(int);
    void summary();
};
project::project()
{

    system("title INVENTORY MANAGEMENT SYSTEM ");
    cout << "-------------------INVENTORY MANAGEMENT SYSTEM------------------- " << endl;

	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "", "oop_cp", 3306, NULL, 0);

	if (conn){
        cout<<"-----------------------DATABASE CONNECTED------------------------";
        cout<<endl;
    }
    else{
        cout<<"FAILED TO CONNECT TO DATABASE";
    }

}
void project::menu()
{

    cout << "\n-----------------------------WELCOME-----------------------------" << endl;

    cout << "1.EDIT ITEM" << endl;
    cout << "2.All Items" << endl;
    cout << "3.Sold Items" << endl;
    cout << "4.Add New Item" << endl;
    cout << "5.Add New Sale" << endl;
    cout << "6.Delete Item" << endl;
    cout << "7.CLEAR SCREEN" << endl;
    cout << "8.REPORTS"<<endl;
    cout << "9.Exit" << endl;
    //cout<<"Enter your choice: "<<endl ;
}
void project::addNewItem()
{
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;

    string name;
    string quantity;
    string price ;
    cout<<"Enter name: ";
    cin>>name;
    cout<<"Enter quantity: ";
    cin>>quantity;
    cout<<"Enter Price   : ";
    cin>>price;
    string query = "select * from items  where name = '"+name+"' ";
    const char* q = query.c_str();
    mysql_query(conn, q);
    res = mysql_store_result(conn);
         if ((row = mysql_fetch_row(res)))
        {
            cout<<"ITEM ALREADY EXISTS"<<endl;

        }

        else
     {
            string ty="1";
            string query = "insert into items (name, quantity,avgprice,date,time) values ('"+name+"','"+quantity+"','"+price+"',curdate(),current_timestamp())";

            const char* q1 = query.c_str();

            qstate = mysql_query(conn, q1);

            string query2 = "insert into sold (type,name, quantity,sellprice,date,time) values ('"+ty+"','"+name+"','"+quantity+"','"+price+"',curdate(),current_timestamp())";

            const char* q2 = query2.c_str();

            qstate = mysql_query(conn, q2);

            if (!qstate)
            {
                cout << endl << "New Item Added." << endl;
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
    }

}
void project::show()
{
    qstate = mysql_query(conn, "select * from items");

    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\n---------------------------------------------------------------\n");
        printf("| %-20s | %-10s | %-10s | %-10s\n", "ID","Item Name", "Quantity","Avg Price");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-20s | %-10s | %-10s | %-10s\n", row[0], row[1], row[2],row[3]);
        }
        printf("---------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}
void project::addNewSale()
{
    string name;
    string quantity;
    string price;
    int cq;
    int nq;
    int qq;
    cout<<"ENTER NAME     : ";
    cin>>name;
    cout<<"ENTER QUANTITY : ";
    cin>>quantity;
    cout<<"ENTER PRICE    : ";
    cin>>price;

    string query = "select * from items  where name = '"+name+"' ";

    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
         res = mysql_store_result(conn);
         if ((row = mysql_fetch_row(res)))
        {
            if (quantity>row[2])
            {
             cout<<"NUMBER OF ITEMS NOT AVAILABLE"<<endl;
            }
            else
            {
                cq=stoi(row[2]);
                qq=stoi(quantity);
                nq=cq-qq;
                string type="0";
                string newquantity=to_string(nq);
                //sold
                string query = "insert into sold (type,name, quantity,sellprice,date,time) values ('"+type+"','"+name+"','"+quantity+"','"+price+"',curdate(),current_timestamp())";
                const char* q = query.c_str();
                qstate = mysql_query(conn, q);
                //update
                string update_query = "update items set quantity = '"+newquantity+"' where name = '"+name+"'";
                q = update_query.c_str();
                qstate = mysql_query(conn, q);

                cout<<"SUCCESS"<<endl;
            }

        }
        else
        {
            cout<<"NO SUCH ITEM IN INVENTORY"<<endl;
        }

    }
    else{
        cout<<"NO";
    }


}
void project::deleteItem()
{
    string name;
    cout<<"ENTER NAME : ";
    cin>>name;


    string query = "select * from items  where name = '"+name+"' ";
    const char* q = query.c_str();
    mysql_query(conn, q);
    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)))
    {
        string query = "DELETE FROM items WHERE name='"+name+"' ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(!qstate)
        {
            cout<<"ITEM DELETED"<<endl;
        }
        else
        {
            cout<<"FAILED"<<endl;
        }
    }
    else
    {
        cout<<"ITEM DOES NOT EXIST"<<endl;
    }





}
void project::editItem()
{
    project::show();
    string id;
    cout<<"Enter item Id to edit: ";
    cin>>id;

    string query = "select * from items where id = '"+id+"'";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);


    if ((row = mysql_fetch_row(res)))
    {
        string typ="1";

        string names=row[1];
        int qtyy=stoi(row[2]);

        string addqty;
        cout<<"ENTER QUANTITY TO ADD :";
        cin>>addqty;
        string prc;
        cout<<"ENTER THE PRICE:  ";
        cin>>prc;
        qtyy=qtyy+stoi(addqty);
        int prewqty= stoi(addqty);
        int prewprc= stoi(prc);
        int num1   = prewprc*prewqty;
        int ans;


        query = "select * from sold where type = '"+typ+"' AND name='"+names+"'   ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            num1=num1+stoi(row[3])*stoi(row[4]);
            prewqty=prewqty+stoi(row[3]);
            ans=num1/prewqty;


        }
        query ="update items set quantity = '"+to_string(qtyy)+"',avgprice='"+to_string(ans)+"' where id = '"+id+"'";
        const char* q1 = query.c_str();
        qstate = mysql_query(conn, q1);


        query= "insert into sold (type,name, quantity,sellprice,date,time) values ('"+typ+"','"+names+"','"+addqty+"','"+prc+"',curdate(),current_timestamp())";
        q1=query.c_str();
        qstate = mysql_query(conn, q1);
        cout<<"DONE"<<endl;

    }
    else
    {
        cout<<"INCORRECT ID ENTERED "<<endl;
    }
}
void project::util()
{





    cout << "-------------------INVENTORY MANAGEMENT SYSTEM------------------- " << endl;
    cout<<"-----------------------DATABASE CONNECTED------------------------";
    project::menu();
}

void project::soldItems()
{
    string ty="0";
    string query = "select * from sold where type = '"+ty+"'";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);


     if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\n---------------------------------------------------------------\n");
        printf("| %-20s | %-10s | %-10s | %-10s\n", "ID","Item Name", "Quantity","SELL PRICE");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-20s | %-10s | %-10s | %-10s\n", row[1], row[2], row[3],row[4]);
        }
        printf("---------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

void project::reportmenu()
{
    cout << "\n-----------------------------WELCOME-----------------------------" << endl;

    cout << "1.GENERAL REPORT " << endl;
    cout << "2.P/L REPORT " << endl;
    cout << "3.INDIVIDUAL PRODUCT REPORT" << endl;
    cout << "4.INVENTORY SUMMARY " << endl;
    cout << "5.GO BACK" << endl;

}

void project::report(int d)
{
    string filename;
    cout<<"ENTER FILE NAME :";
    cin>>filename;
    filename=filename + ".csv";

    string days="-"+to_string(d);


    string check;
    ofstream myfile;
    myfile.open(filename);

    string query = "select * from sold where date <= curdate() and date > date_add(curdate(),interval "+days+" day)   ";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        myfile<<"TYPE"<<","<<"NAME"<<","<<"QTY"<<","<<"PRICE"<<","<<"DATE"<<","<<"TIME"<<endl;
        myfile<<endl;
        while ((row = mysql_fetch_row(res)))
        {
            string s="BUY";
            check=(string)row[0];
            if (check=="0")
            {
                s="SELL";
            }

            myfile<<s<<","<<row[2]<<","<<row[3]<<","<<row[4]<<","<<row[5]<<","<<row[6]<<endl;


        }
        printf("--------------------------------------------------------------------\n");
        cout<<"DONE"<<endl;
    }
    else
    {
        cout<<"failed"<<endl;
    }

}

void project::pL(int d )
{
    string filename;
    cout<<"ENTER FILE NAME :";
    cin>>filename;
    filename=filename + ".csv";
    ofstream myfile;
    myfile.open(filename);
    myfile<<"NAME"<<","<<"BUY VOLUME "<<","<<"SELL VOLUME"<<","<<"AVAILABLE QTY"<<","<<"P/L"<<endl;
    myfile<<endl;
    int netpl=0;
    string days="-"+to_string(d);


    qstate = mysql_query(conn, "select * from items");
    res = mysql_store_result(conn);
    while ((row = mysql_fetch_row(res)))
    {
        int buyvol=0;
        int sellvol=0;
        int pl=0;
        string name=(string)row[1];

        string query = "select * from sold where name = '"+name+"' and date <= curdate() and date > date_add(curdate(),interval "+days+" day)   ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        res1 = mysql_store_result(conn);
        while ((row1 = mysql_fetch_row(res1)))
        {

            string check;
            check=(string)row1[0];
            if (check=="1")
            {
                buyvol=buyvol+stoi((string)row1[3]);
            }
            else
            {
                sellvol=sellvol+stoi((string)row1[3]);
                int diff = stoi((string)row1[4]) - stoi((string)row[3]);
                pl=pl+ diff*stoi((string)row1[3]);

            }
        }
        netpl=netpl+pl;
        myfile<<name<<","<<buyvol<<","<<sellvol<<","<<row[2]<<","<<pl<<endl;

    }
    myfile<<endl;
    myfile<<""<<","<<""<<","<<""<<","<<"NET P/L"<<","<<netpl<<endl;
    printf("--------------------------------------------------------------------\n");
    cout<<"DONE"<<endl;

}

void project ::individual_report(int d)
{
    string days="-"+to_string(d);
    string name;
    cout<<"ENTER NAME    : ";
    cin>>name;
    string query = "select * from items  where name = '"+name+"' ";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)))
    {

        string check;

        string filename;
        cout<<"ENTER FILE NAME :";
        cin>>filename;
        filename=filename + ".csv";
        ofstream myfile;
        myfile.open(filename);
        myfile<<"PRODUCT NAME : "+ name<<endl;
        myfile<<endl;
        myfile<<"TYPE"<<","<<"QTY"<<","<<"PRICE"<<","<<"DATE"<<","<<"TIME"<<endl;
        myfile<<endl;
        string query = "select * from sold where name = '"+name+"' and date <= curdate() and date > date_add(curdate(),interval "+days+" day)   ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        res1 = mysql_store_result(conn);
        while ((row1 = mysql_fetch_row(res1)))
        {
            string s="BUY";
            check=(string)row1[0];
            if (check=="0")
            {
                s="SELL";
            }
            myfile<<s<<","<<row1[3]<<","<<row1[4]<<","<<row1[5]<<","<<row1[6]<<endl;
        }
        printf("--------------------------------------------------------------------\n");
        cout<<"DONE"<<endl;

    }
    else
    {
        cout<<"NO SUCH ITEM "<<endl;
    }

}

void project::summary()
{
    string filename;
    cout<<"ENTER FILE NAME :";
    cin>>filename;
    filename=filename + ".csv";
    ofstream myfile;
    myfile.open(filename);
    myfile<<"INVENTORY SUMMARY"<<endl;
    myfile<<endl;
    myfile<<"NAME"<<","<<"AVAILABLE QTY"<<","<<"AVG PRICE"<<endl;
    qstate = mysql_query(conn, "select * from items");
    res = mysql_store_result(conn);
    while ((row = mysql_fetch_row(res)))
     {
         myfile<<row[1]<<","<<row[2]<<","<<row[3]<<endl;

     }
     printf("--------------------------------------------------------------------\n");
     cout<<"DONE"<<endl;



}
int main()
{
    int choice;
    int choice_internal;
    bool state=true;
    bool state_internal=false;

    project p1;
    p1.menu();


    while(state)
    {

        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"ENTER CHOICE    : ";
        cin>>choice;
         if (choice==1)
        {
            p1.editItem();
        }
        if (choice==2)
        {
            p1.show();
        }
         if (choice==3)
        {
            p1.soldItems();
        }
        if (choice==4)
        {
            p1.addNewItem();
        }
        if (choice==5)
        {
            p1.addNewSale();
        }
        if (choice==6)
        {
            p1.deleteItem();
        }
        if (choice==7)
        {
            system("cls");
            p1.util();
        }
        if (choice==8){
            system("cls");
            state_internal=true;
            p1.reportmenu();
            while(state_internal)
            {
                cout<<"-----------------------------------------------------------------"<<endl;
                cout<<"ENTER CHOICE : ";
                cin>>choice_internal;
                if (choice_internal==1)
                {
                    int d;
                    cout<<"ENTER DAYS :";
                    cin>>d;
                    p1.report(d);
                }
                if (choice_internal==2)
                {
                    int d;
                    cout<<"ENTER DAYS :";
                    cin>>d;
                    p1.pL(d);

                }
                if (choice_internal==3)
                {
                    int d;
                    cout<<"ENTER DAYS :";
                    cin>>d;
                    p1.individual_report(d);

                }
                if (choice_internal==4)
                {
                    p1.summary();
                }
                if (choice_internal==5)
                {
                    state_internal=false;
                    system("cls");
                    p1.util();
                }

            }

        }
        if (choice==9)
        {
             cout << "\n----------------------------THANK YOU----------------------------" << endl;
            state=false;
        }

    }

}
