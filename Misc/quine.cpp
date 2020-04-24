#include <iostream>
std::string A(){return "void B(std::string M){std::cout << \"#include <iostream>\\nstring A(){return \"\" + M + \"\";}\" + \"\\n\" + M + \"\\nint main(){ B(A()); return 0; }\";";}
void B(std::string M){std::cout << "#include <iostream>\nstring A(){return \"" + M + "\";}" + "\n" + M + "\nint main(){ B(A()); return 0; }";}
int main(){ B(A()); return 0; }