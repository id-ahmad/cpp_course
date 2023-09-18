#include <string>
#include <iostream>
/*
 * namespace
 */

/*
if compiler (if in the same file) or the linker (if in diff files) can't tell apart two identifiers, an error will be issued.
this is called naming collision.

examples: vars with the same name will collide.
          fcts with the same signature will collide.
*/

/*
namesapces are introduced to confine identifiers in a space that owns them. Identifiers should only be unique inside the namespace, but
can be reused outside in other namespaces or in the global namespace.
namespace can be used to group semantically related identifiers.

examples :
        global namespace : it's the namespace outside any local space defined in the program (namespace, fct, class..)
        std namespace: the standard namespace used by the STL. It's purpose is to prevent identiers defined in the STL from colliding with any
        user-defined identifier.
*/

namespace course // course is a user-defined namespace
{
    std::string course_name; // std:: used to resolve the namespace the object string belongs to.
    int total_hours;
}

int main()
{
    course::course_name = "C++";
    course::total_hours = 50;
    std::cout << "course name: " << course::course_name << '\n'; // cout is an object defined in the std namespace
    return 0;
}
