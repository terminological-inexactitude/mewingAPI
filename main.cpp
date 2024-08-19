#include <cstdio>

#define usertag {id}LL
#define turk "<a:dancing_turk:823716821915926549>"

int main() {  
    int rows = 6;
    int cols = 9;

	printf("# ");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) { 
            printf("%s", turk);
        }
        if (i < rows - 1) {
            printf("\n# ");
        }
    }

    /*
    printf("Your emoji of today is:\n# <:kleiner_happy:363444088965431298>");
    printf("# <:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298>\n");
    printf("# <:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298>\n");
    printf("# <:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298><:kleiner_happy:363444088965431298>\n");
    
    printf("\n");
    printf("<:skibid:1207635444909481984>\n");
    printf("# <:skibid:1207635444909481984>");

    printf("%lld", usertag);
    */
    
    return 0;
}
