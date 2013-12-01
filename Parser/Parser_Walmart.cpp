#include<iostream>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<curl/curl.h>
#include<tr1/unordered_map>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
//#include<tr1/pair.h>

using namespace std;

void parseProductsName(string, tr1::unordered_map<int,string>&);
void parseProductsPrice(string, tr1::unordered_map<int,string>&);
void associateProductNameAndPrice(tr1::unordered_map<int,string>& , tr1::unordered_map<int,string>&, tr1::unordered_map<string,string>&);
string getHTMLSource(string);
size_t curl_to_string(void *ptr, size_t size, size_t nmemb, void *data);

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

int main (int argc, char *argv[])
{
   if((new string(argv[1]))->compare(*(new string("fetch"))) == 0)
     {
       ifstream ifs;
       ofstream ofs;
       string pathToReadFile = "crawledData_Walmart/linkdb/links";
       string pathToWriteFile = "results/";
       mkdir(pathToWriteFile.c_str(), S_IRWXU);

       ifs.open(pathToReadFile.c_str(), std::fstream::in);
       ofs.open((pathToWriteFile + "productDetails_Walmart").c_str(), std::fstream::out | std::fstream::app);

       char line[1024];
       int count = 0;

       while( ifs.good() )
         {
           ifs.getline(line, 1024);
           string lineS = line;
           istringstream ss(lineS);
           string token;
           //bool fromUrlToken = false;
           //bool httpUrlToken = false;

           while( (ss >> token) )
             {
              if( (token.size() > 7) && (token.substr(0, 7)=="http://") )
               {
                 //parseDocument(token, ofs);
                 string page = getHTMLSource(token);
                 tr1::unordered_map<int,string> productList;
        	 parseProductsName(page,productList);
	         tr1::unordered_map<int,string> productPrice;
        	 parseProductsPrice(page,productPrice);
	         tr1::unordered_map<string, string> association;
        	 associateProductNameAndPrice(productList, productPrice, association);
	         tr1::unordered_map<string, string>::iterator stritr = association.begin();
        	 tr1::unordered_map<string, string>::iterator enditr = association.end();

	         while(stritr != enditr)
        	   {
	             ofs<<"Product Name::::"<<stritr->first<<"::::Product Price::::"<<stritr->second<<"::::URL::::"<<token<<"::::Store::::Ebay"<<endl;
	             stritr++;
	           }
                 count = count + 1;
                 cout<<"LINK NO. "<<count<<endl;
               }
              else if(token == "fromUrl:")
                {
                  if(ss >> token)
                   {
                     //parseDocument(token, ofs);
                     string page = getHTMLSource(token);
	             tr1::unordered_map<int,string> productList;
               	     parseProductsName(page,productList);
	             tr1::unordered_map<int,string> productPrice;
	             parseProductsPrice(page,productPrice);
	             tr1::unordered_map<string, string> association;
	             associateProductNameAndPrice(productList, productPrice, association);
	             tr1::unordered_map<string, string>::iterator stritr = association.begin();
	             tr1::unordered_map<string, string>::iterator enditr = association.end();

                     while(stritr != enditr)
                       {
                         ofs<<"Product Name::::"<<stritr->first<<"::::Product Price::::"<<stritr->second<<"::::URL::::"<<token<<"::::Store::::Ebay"<<endl;
                         stritr++;
                       }
                     count = count + 1;
                     cout<<"LINK NO. "<<count<<endl;
                   }
                }
             }
         }
/*
         string page = getHTMLSource("http://www.ebay.com/sch/Jeans-/11483/i.html?");
         tr1::unordered_map<int,string> productList;
	 parseProductsName(page,productList);
	 tr1::unordered_map<int,string> productPrice;
	 parseProductsPrice(page,productPrice);
	 tr1::unordered_map<string, string> association;
	 associateProductNameAndPrice(productList, productPrice, association);
	 tr1::unordered_map<string, string>::iterator stritr = association.begin();
	 tr1::unordered_map<string, string>::iterator enditr = association.end();

	 while(stritr != enditr)
	   {
             cout<<"Product Name: "<<stritr->first<<" Product Price: "<<stritr->second<<endl;
             stritr++;
           }
         */
         ofs.close();
         return 0;
     }
     else if((new string(argv[1]))->compare(*(new string("nofetch"))) == 0)
       {
          ifstream ifs;
          ofstream ofs;
          //string pathToReadFile = "crawledData_Walmart/seg/dump";
          string pathToReadFile = "walmart_page";
          string pathToWriteFile = "results/";
          mkdir(pathToWriteFile.c_str(), S_IRWXU);

          ifs.open(pathToReadFile.c_str(), std::fstream::in);
          ofs.open((pathToWriteFile + "productDetails_Walmart").c_str(), std::fstream::out | std::fstream::app);

          int count = 0;

          int read=0;
          ifs.seekg (0, ifs.end);
          int length = ifs.tellg();
          ifs.seekg (0, ifs.beg);

          while( ifs.good() && read < length)
           {
             cout<<"Iterating while loop "<<endl;
             char * buffer = new char [102400];
             ifs.read(buffer, 102400);
             string page = buffer;

             tr1::unordered_map<int,string> productList;
             parseProductsName(page,productList);
             //cout<<"Name Parsed"<<endl;
             tr1::unordered_map<int,string> productPrice;
             parseProductsPrice(page,productPrice);
             //cout<<"Price Parsed"<<endl;
             tr1::unordered_map<string, string> association;
             associateProductNameAndPrice(productList, productPrice, association);
             //cout<<"Associated"<<endl;
             tr1::unordered_map<string, string>::iterator stritr = association.begin();
             tr1::unordered_map<string, string>::iterator enditr = association.end();

             while(stritr != enditr)
               {
                 ofs<<"Product Name::::"<<stritr->first<<"::::Product Price::::"<<stritr->second<<"::::Store::::Walmart"<<endl;
                 stritr++;
               }

             //cout<<"iteration done"<<endl;

             read = read + 102400;
           }

          ofs.close();
          return 0;
       }
}


void parseProductsName(string page, tr1::unordered_map<int,string> &productList)
{
    //cout<<"Page is: "<<page<<endl<<"--------------------------"<<endl<<endl;
    int lineNumber = 1;
    //tr1::unordered_map<int,string> productList;

    //url = url + "\n";
    //ofs.write(url.c_str(), url.size());
    //cout<<url<<endl;

    //string page =  getHTMLSource(url);
    int i = 0;
    int size = page.size();
    //cout<<endl<<"size is "<<size;

    while(i < size)
      {
          while(i < size && page[i] != '<')
            {
              if(page[i] == '\n')
                lineNumber++;
              i++;
            }

          i++;
          string link = "<";
          if(i+31 < size && page.substr(i,31).compare("a class=\"prodLink GridItemLink\"")==0 )
            {
                cout<<"found prodLink"<<endl;
                while(i+3<size && (page[i] != '<' || page[i+1] != '/' || page[i+2] != 'a' || page[i+3] != '>' ) )
                  {
                    link = link + page[i];
                    if(page[i] == '\n')
                      lineNumber++;
                    i++;
                  }
                //cout<<"link is: "<<link;

                size_t pos = link.find("href=\"");
                if (pos != string::npos)
                   {
                      cout<<"Found href";
                      pos = link.find_last_of(">");
                      if (pos != string::npos)
                         {
                           stringstream links(link);
                           string token;
                           links >> token;
                           links >> token;
                           links >> token;
                           links >> token;
                           string url = "\"www.walmart.com";
                           if(token.substr(0,4) == "href")
                             url = url + token.substr(6);
                           //cout<<"Url is: "<<url;
                           //return;

                           //int index = pos + 1;
                           //cout<<link.substr(index)<<endl<<endl;
                           size_t post = link.find("title=\"");
                           post = post + 7;
                           string productItem = "";
                           while(post+1<size && ( link[post] !='\"' || link[post+1] != '>' ) )
                             {
                              productItem = productItem + link[post];
                              post = post + 1;
                             }
                           productItem = productItem + "::::URL::::" + url;
                           productItem = trim(productItem);
                           //cout<<productItem<<endl;
                           pair<tr1::unordered_map<int,string>::iterator, bool> res = productList.insert(make_pair<int,string> (lineNumber, productItem));
                           if(res.second == false)
                             {
                              //cout<<"At line number "<<lineNumber<<" entry already exist "<<endl;
                              //cout<<"name is: "<<productItem<<endl;
                             }
                         }
                      else
                         {
                           cout<<"No product here "<<endl;
                         }
                      //cout<<link<<endl;
                   }

                i = i+3;
            }
      }//end while

    //cout<<endl<<endl<<page<<endl<<endl;

    /*tr1::unordered_map<int,string>::iterator stritr = productList.begin();
    tr1::unordered_map<int,string>::iterator enditr = productList.end();
    while(stritr != enditr)
      {
        cout<<"Line number is: "<<stritr->first<<" Product is: "<<stritr->second<<endl;
        stritr++;
      }
    */

}

void parseProductsPrice(string page, tr1::unordered_map<int,string> &productPrice)
{

    int lineNumber = 1;
    //tr1::unordered_map<int,string> productList;

    //url = url + "\n";
    //ofs.write(url.c_str(), url.size());
    //cout<<url<<endl;

    //string page =  getHTMLSource(url);
    int i = 0;
    int size = page.size();
    //cout<<endl<<"size is "<<size;

    while(i < size)
      {
          while(i < size && page[i] != '<')
            {
              if(page[i] == '\n')
                lineNumber++;
              i++;
            }

          i++;
          string link = "<";
          if(i+3 < size && (page[i] == 's' && page[i+1] == 'p' && page[i+2] == 'a' && page[i+3] == 'n') )
            {
                while(i+6< size && (page[i] != '<' || page[i+1] != '/'  || page[i+2] != 's' || page[i+3] != 'p' || page[i+4] != 'a' || page[i+5] != 'n' || page[i+6] != '>' ) )
                  {
                    link = link + page[i];
                    if(page[i] == '\n')
                      lineNumber++;
                    i++;
                  }

                size_t pos = link.find("class=\"bigPriceText2\"");
                if (pos != string::npos)
                   {
                      pos = link.find_last_of(">");
                      if (pos != string::npos)
                         {
                           int index = pos + 1;
                           //cout<<link.substr(index)<<endl<<endl;
                           string priceItem = link.substr(index);
                           priceItem=trim(priceItem);
                           int length = priceItem.length();
                           priceItem = priceItem.substr(0, length-1);
                           //cout<<"PriceItem: "<<priceItem<<endl;
                           pair<tr1::unordered_map<int,string>::iterator, bool> res = productPrice.insert(make_pair<int,string> (lineNumber, priceItem));
                           if(res.second == false)
                              { //cout<<"At line number "<<lineNumber<<" entry already exist "<<endl;
                              }
                         }
                      else
                         {
                           cout<<"No product here "<<endl;
                         }
                      //cout<<link<<endl;
                   }

                i = i+2;
            }
      }//end while

    //cout<<endl<<endl<<page<<endl<<endl;

    tr1::unordered_map<int,string>::iterator stritr = productPrice.begin();
    tr1::unordered_map<int,string>::iterator enditr = productPrice.end();
    while(stritr != enditr)
      {
        //cout<<"Line number is: "<<stritr->first<<" Product Price is: "<<stritr->second<<endl;
        stritr++;
      }


}

void associateProductNameAndPrice(tr1::unordered_map<int,string>& productName, tr1::unordered_map<int,string>& productPrice, tr1::unordered_map<string, string>& association)
{
  tr1::unordered_map<int, string>::iterator stritr = productName.begin();
  tr1::unordered_map<int, string>::iterator enditr = productName.end();

  while(stritr != enditr)
    {
       int lineNumber = stritr->first;
       string productName = stritr->second;

       bool foundMatch = false;

       int searchDistance = 100;
       int forwardSearch = 0;
       int backwardSearch = 0;

       while(!foundMatch && forwardSearch<searchDistance)
         {
           tr1::unordered_map<int, string>::iterator find = productPrice.find(lineNumber+forwardSearch);
           if(find != productPrice.end())
             {
                association.insert(make_pair<string,string> (productName, find->second));
                foundMatch = true;
             }
           else
             forwardSearch++;
         }

       while(!foundMatch && backwardSearch<searchDistance)
         {
           tr1::unordered_map<int, string>::iterator find = productPrice.find(lineNumber-backwardSearch);
           if(find != productPrice.end())
             {
                association.insert(make_pair<string,string> (productName, find->second));
                foundMatch = true;
             }
           else
             backwardSearch++;
         }


       if(foundMatch == false)
          association.insert(make_pair<string,string> (productName, "EMPTY"));

       stritr++;
    }
}


string getHTMLSource(string url)
{
  CURL *curl;
  CURLcode res;
  string urlN;
  string pagedata;
  ofstream ofs("pages.txt", std::fstream::out | std::fstream::app);

  /* if( url.substr(0, 7) == "http://" )
    {
      int size = url.size();
      urlN = url.substr(7,size-7);
    }
  else if(url.substr(0, 8) == "https://")
    {
      int size = url.size();
      urlN = url.substr(8, size-8);
    }
*/



  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &pagedata);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    else
      {
        curl_easy_cleanup(curl);
        ofs.write(pagedata.c_str(), pagedata.size());
        ofs.close();
        return pagedata;
      }
  }
    curl_easy_cleanup(curl);
    ofs.close();
    return " ";
}

size_t curl_to_string(void *ptr, size_t size, size_t nmemb, void *data)
{
    std::string *str = (std::string *) data;
    char *sptr = (char *) ptr;
    int x;
    for(x = 0; x < size * nmemb; ++x)
    {
        (*str) += sptr[x];
    }

    return size * nmemb;
}
