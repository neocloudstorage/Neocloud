#include<iostream>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<curl/curl.h>

using namespace std;

void parseDocument(string, ofstream&);
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

    //parseDocument("http://www.ebay.com/sch/Jeans-/11483/i.html?" , ofs);
    ofs.close();
    return 0;
}


void parseDocument(string url, ofstream &ofs)
{

    url = url + "\n";
    ofs.write(url.c_str(), url.size());
    cout<<url<<endl;

    string page =  getHTMLSource(url);
    int i = 0;
    int size = page.size();
    cout<<endl<<"size is "<<size;

    while(i < size)
      {
          while(i < size && page[i] != '<')
              i++;

          i++;
          string link = "<";
          if(i < size && page[i] == 'a')
            {
                while(i+2< size && (page[i] != '/' || page[i+1] != 'a' || page[i+2] != '>' ) )
                  {
                    link = link + page[i];
                    i++;
                  }

                size_t pos = link.find("itemprop=\"name\"");
                if (pos != string::npos)
                   {
                      pos = link.find_last_of(">");
                      if (pos != string::npos)
                         {
                           int index = pos + 1;
                           cout<<link.substr(index)<<endl;
                         }
                      else
                         {
                           cout<<"No present"<<endl;
                         }
                      //cout<<link<<endl;
                   }

                i = i+3;
            }
      }

    //cout<<endl<<endl<<page<<endl<<endl;
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
