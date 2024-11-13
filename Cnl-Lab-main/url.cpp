#include <iostream>
#include <string>

using namespace std;

struct URLComponents {
    string scheme;
    string host;
    string path;
    string query;
};

URLComponents splitURL(const string& url) {
    URLComponents components;
    
   
    size_t scheme_end = url.find("://");
    if (scheme_end != string::npos) {
        components.scheme = url.substr(0, scheme_end);
    } else {
        cout << "Invalid URL format: missing scheme." << endl;
        return components;
    }
    

    size_t host_start = scheme_end + 3;
    size_t path_start = url.find('/', host_start);
    if (path_start != string::npos) {
        components.host = url.substr(host_start, path_start - host_start);
    } else {
        components.host = url.substr(host_start);
        return components;
    }

  
    size_t query_start = url.find('?', path_start);
    if (query_start != string::npos) {
        components.path = url.substr(path_start, query_start - path_start);
    } else {
        components.path = url.substr(path_start);
        return components;
    }


    components.query = url.substr(query_start + 1);
    
    return components;
}

int main() {
    string url;
    cout << "Enter a URL: ";
    getline(cin, url);

    URLComponents components = splitURL(url);

    cout << "Scheme: " << components.scheme << endl;
    cout << "Host: " << components.host << endl;
    cout << "Path: " << components.path << endl;
    cout << "Query: " << components.query << endl;

    return 0;
}
