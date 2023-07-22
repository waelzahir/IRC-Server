#include <iostream>
#include <sstream>

int main() {
    std::stringstream ss;

    // Insert some content into the stringstream
    ss << "This is a sample text.";

    // Manipulate the content, for example, let's add "Hello, " to the front
    std::cout << ss.str() << std::endl;
    std::string prefix = "Hello, ";
    ss.seekp(0); // Set the put pointer to the beginning of the stringstream
    ss << prefix; // Overwrite the existing content with the prefix

    std::string x = "";
    ss >> x;
    // Output the updated content of the stringstream
    std::cout <<  x << std::endl;

    return 0;
}
