#include<iostream>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<curl/curl.h>
#include<tr1/unordered_map>
//#include<tr1/pair.h>

using namespace std;

void parseProductsName(string, tr1::unordered_map<int,string>&);
void parseProductsPrice(string, tr1::unordered_map<int,string>&);
void associateProductNameAndPrice(tr1::unordered_map<int,string>& , tr1::unordered_map<int,string>&, tr1::unordered_map<string,string>&);
string getHTMLSource(string);
size_t curl_to_string(void *ptr, size_t size, size_t nmemb, void *data);

int main ()
{
   ifstream ifs;
   ofstream ofs;
   string pathToReadFile = "crawledData/linkdb/links";
   string pathToWriteFile = "results/";
   mkdir(pathToWriteFile.c_str(), S_IRWXU);

   ifs.open(pathToReadFile.c_str(), std::fstream::in);
   ofs.open((pathToWriteFile + "productDetails").c_str(), std::fstream::out | std::fstream::app);

   char line[1024];
   int count = 0;
/*
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
                parseDocument(token, ofs);
                count = count + 1;
             }
           else if(token == "fromUrl:")
             {
                if(ss >> token)
                  {
                     parseDocument(token, ofs);
                     count = count + 1;
                  }
                 //else
                 // {
                 //    fromUrlToken = true;
                 // }
             }
         }
    }
*/

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

    ofs.close();
    return 0;
}


void parseProductsName(string page, tr1::unordered_map<int,string> &productList)
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
          if(i < size && page[i] == 'a')
            {
                while(i+3< size && (page[i] != '<' || page[i+1] != '/' || page[i+2] != 'a' || page[i+3] != '>' ) )
                  {
                    link = link + page[i];
                    if(page[i] == '\n')
                      lineNumber++;
                    i++;
                  }

                size_t pos = link.find("itemprop=\"name\"");
                if (pos != string::npos)
                   {
                      pos = link.find_last_of(">");
                      if (pos != string::npos)
                         {
                           int index = pos + 1;
                           //cout<<link.substr(index)<<endl<<endl;
                           string productItem = link.substr(index);
                           pair<tr1::unordered_map<int,string>::iterator, bool> res = productList.insert(make_pair<int,string> (lineNumber, productItem));
                           if(res.second == false)
                              cout<<"At this line number entry already exist "<<endl;
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

    tr1::unordered_map<int,string>::iterator stritr = productList.begin();
    tr1::unordered_map<int,string>::iterator enditr = productList.end();
    while(stritr != enditr)
      {
        cout<<"Line number is: "<<stritr->first<<" Product is: "<<stritr->second<<endl;
        stritr++;
      }


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
          if(i+3 < size && page[i] == 's' && page[i+1] == 'p' && page[i+2] == 'a' && page[i+3] == 'n')
            {
                while(i+6< size && (page[i] != '<' || page[i+1] != '/' || page[i+2] != 's' || page[i+3] != 'p' || page[i+4] != 'a' || page[i+5] != 'n' || page[i+6] != '>' ) )
                  {
                    link = link + page[i];
                    if(page[i] == '\n')
                      lineNumber++;
                    i++;
                  }

                size_t pos = link.find("itemprop=\"price\"");
                if (pos != string::npos)
                   {
                      pos = link.find_last_of(">");
                      if (pos != string::npos)
                         {
                           int index = pos + 1;
                           //cout<<link.substr(index)<<endl<<endl;
                           string priceItem = link.substr(index);
                           pair<tr1::unordered_map<int,string>::iterator, bool> res = productPrice.insert(make_pair<int,string> (lineNumber, priceItem));
                           if(res.second == false)
                              cout<<"At this line number entry already exist "<<endl;
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

    tr1::unordered_map<int,string>::iterator stritr = productPrice.begin();
    tr1::unordered_map<int,string>::iterator enditr = productPrice.end();
    while(stritr != enditr)
      {
        cout<<"Line number is: "<<stritr->first<<" Product Price is: "<<stritr->second<<endl;
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

       int searchDistance = 20;
       int forwardSearch = 0;

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
