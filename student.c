#include "stdio.h"
#include<time.h>
#include<string.h>
#include <stdio.h>
#include <poll.h>
#include  <unistd.h>
/*定义学生结构体*/

struct Student {
    char ID[20];
    char Name[20];
    char Sex[20];
    float math;
    float english;
    float sum;
    float average;
};


/*声明学生数组及学生数量*/

struct Student students[1000];

char FILEPATH[] = "/Users/paizhu/Downloads/chengji_back.txt";
int TimeOutMilliSeconds = 5 * 1000;
int num = 0;

float avg(struct Student stu) {
    return (stu.math + stu.english) / 2;
}

//求总分值
float sum(struct Student stu) {
    return (stu.math + stu.english);
}

//通过学号返回数组下标

int Student_SearchByIndex(char id[]) {
    int i;
    for (i = 0; i < num; i++) {
        if (strcmp(students[i].ID, id) == 0) {
            return i;
        }
    }
    return -1;
}


/*通过姓名返回数组下标*/

int Student_SearchByName(char name[]) {
    int i;
    for (i = 0; i < num; i++) {
        if (strcmp(students[i].Name, name) == 0) {
            return i;
        }
    }
    return -1;
}


/*显示单条学生记录*/

void Student_DisplaySingle(int index) {
    printf("%10s%10s%20s%20s%20s%20s%20s\n", "学号", "姓名", "性别", "英语成绩", "高数成绩", "总分成绩", "平均成绩");
    printf("-------------------------------------------------------------\n");
    printf("%10s%10s%10s%10.2f%10.2f%10.2f%10.2f\n", students[index].ID, students[index].Name, students[index].Sex,
           students[index].math, students[index].english, students[index].sum, students[index].average);
}


/*插入学生信息*/

void Student_Insert() {
    while (1) {
        printf("请输入学号,姓名,性别,英语成绩,高数成绩:");
        printf("\n\n");
        scanf("%s%s%s%f%f", &students[num].ID, &students[num].Name, &students[num].Sex, &students[num].math,
              &students[num].english);
        getchar();
        students[num].sum = sum(students[num]);
        students[num].average = avg(students[num]);
        num++;
        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}


/*修改学生信息*/
void Student_Modify() {
    //float mark1,mark2,mark3;
    while (1) {
        char id[20];
        int index;
        printf("请输入要修改的学生的学号:");
        scanf("%s", &id);
        getchar();
        index = Student_SearchByIndex(id);
        if (index == -1) {
            printf("学生不存在!\n");
        } else {
            printf("你要修改的学生信息为:\n");
            Student_DisplaySingle(index);
            printf("-- 请输入新值--\n");
            printf("请输入学号,姓名,性别,英语成绩,高数成绩:");
            printf("\n\n");
            scanf("%s%s%s%f%f", &students[index].ID, &students[index].Name, &students[index].Sex, &students[index].math,
                  &students[index].english);
            getchar();
            students[index].sum = sum(students[index]);
            students[index].average = avg(students[index]);
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}


/*删除学生信息*/

void Student_Delete() {
    int i;
    while (1) {
        char id[20];

        int index;
        printf("请输入要删除的学生的学号:");
        scanf("%s", &id);
        getchar();
        index = Student_SearchByIndex(id);
        if (index == -1) {
            printf("学生不存在!\n");
        } else {
            printf("你要删除的学生信息为:\n");
            Student_DisplaySingle(index);
            printf("是否真的要删除?(y/n)");
            if (getchar() == 'y') {
                for (i = index; i < num - 1; i++) {
                    students[i] = students[i + 1];//把后边的对象都向前移动

                }
                num--;
            }
            getchar();
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}


/*按学号查询*/

void Student_Select() {
    while (1) {
        char ID[20];

        int index;
        printf("请输入要查询的学生的学号:");
        scanf("%s", &ID);
        getchar();
        index = Student_SearchByIndex(ID);
        if (index == -1) {
            printf("学生不存在!\n");
        } else {
            printf("你要查询的学生信息为:\n");
            Student_DisplaySingle(index);
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}


/*按总分值排序*/

void Student_SortBysum() {
    int i, j;

    struct Student tmp;
    for (i = 0; i < num; i++) {
        for (j = 1; j < num - i; j++) {
            if (students[j - 1].sum < students[j].sum) {
                tmp = students[j - 1];
                students[j - 1] = students[j];
                students[j] = tmp;
            }
        }
    }
}

void Student_SortByMath() {
    int i, j;
    struct Student yy;
    for (i = 0; i < num; i++) {
        for (j = 1; j < num - i; j++) {
            if (students[j - 1].math < students[j].math) {
                yy = students[j - 1];
                students[j - 1] = students[j];
                students[j] = yy;
            }
        }
    }
}


void Student_SortByEnglish() {
    int i, j;
    struct Student gs;
    for (i = 0; i < num; i++) {
        for (j = 1; j < num - i; j++) {
            if (students[j - 1].english < students[j].english) {
                gs = students[j - 1];
                students[j - 1] = students[j];
                students[j] = gs;
            }
        }
    }
}


void Student_No1() {
    int i;
    for (i = 0; i < num; i++) {
        if (students[i].math < 60) {
            printf("%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "性别", "英语成绩", "高数成绩", "总分成绩", "平均成绩");
            printf("--------------------------------------------------------------------------------\n");
            printf("%10s%10s%10s%10.2f%10.2f%10.2f%10.2f\n", students[i].ID, students[i].Name, students[i].Sex,
                   students[i].math, students[i].english, students[i].sum, students[i].average);
        }
    }
}

void Student_No2() {
    int i;
    for (i = 0; i < num; i++) {
        if (students[i].english < 60) {
            printf("%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "性别", "英语成绩", "高数成绩", "总分成绩", "平均成绩");
            printf("--------------------------------------------------------------------------------\n");
            printf("%10s%10s%10s%10.2f%10.2f%10.2f%10.2f\n", students[i].ID, students[i].Name, students[i].Sex,
                   students[i].math, students[i].english, students[i].sum, students[i].average);
        }
    }
}

void averageScoreByGender() {
    float totalScoreMale = 0;
    float totalScoreFeMale = 0;
    int numOfMale = 0;
    int numOfFemale = 0;
    for (int i = 0; i < num; i++) {
        if (strcmp(students[i].Sex, "Male")) {
            totalScoreMale += students[i].average;
            numOfMale++;
        } else if (strcmp(students[i].Sex, "Female")) {
            totalScoreFeMale += students[i].average;
            numOfFemale++;
        }
    }
    printf("--------------------------------------------------------------------------------\n");
    if (numOfMale == 0) {
        printf("No Boys in the system \n\n");
    } else {
        printf("The average score of boys is %10.2f \n\n", totalScoreMale / numOfMale);
    }
    if (numOfFemale == 0) {
        printf("No Girls in the system \n\n");
    } else {
        printf("The average score of girls is %10.2f \n", totalScoreFeMale / numOfFemale);
    }
    printf("--------------------------------------------------------------------------------\n");
}


void Student_bijiao() {
    int j, k;
    printf("请输入你的总分：");
    scanf("%10d", &k);
    for (j = 0; j < num; j++)
        if (students[j].sum > k) {
            printf("%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "性别", "英语成绩", "高数成绩", "总分成绩", "平均成绩");
            printf("--------------------------------------------------------------------------------\n");
            printf("%10s%10s%10s%10.2f%10.2f%10.2f%10.2f\n", students[j].ID, students[j].Name, students[j].Sex,
                   students[j].math, students[j].english, students[j].sum, students[j].average);
        }
}


/*显示学生信息*/

void Student_Display() {
    int i;
    printf("%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "性别", "英语成绩", "高数成绩", "总分成绩", "平均成绩");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < num; i++) {
        printf("%10s%10s%10s%10.2f%10.2f%10.2f%10.2f\n", students[i].ID, students[i].Name, students[i].Sex,
               students[i].math, students[i].english, students[i].sum, students[i].average);
    }
}


/*将学生信息从文件读出*/

void IO_ReadInfo() {
    FILE *fp;

    int i;
    if ((fp = fopen(FILEPATH, "rb")) == NULL) {
        printf("不能打开文件!\n");
        return;
    }
    if (fread(&num, sizeof(int), 1, fp) != 1) {
        num = -1;
    } else {
        for (i = 0; i < num; i++) {
            fread(&students[i], sizeof(struct Student), 1, fp);
        }
    }
    fclose(fp);
}


/*将学生信息写入文件*/

void IO_WriteInfo() {
    FILE *fp;

    int i;
    if ((fp = fopen(FILEPATH, "wb")) == NULL) {
        printf("不能打开文件!\n");
        return;
    }
    if (fwrite(&num, sizeof(int), 1, fp) != 1) {
        printf("写入文件错误!\n");
    }
    for (i = 0; i < num; i++) {
        if (fwrite(&students[i], sizeof(struct Student), 1, fp) != 1) {
            printf("写入文件错误!\n");
        }
    }
    fclose(fp);
}


void Student_xs() {
    int choice;
    IO_ReadInfo();
    struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};

    while (1) {
        printf("1. 按学号查询学生记录\n");
        printf("2. 查询总分高于你的学生\n");
        printf("3. 退出\n");

        if (poll(&mypoll, 1, TimeOutMilliSeconds)) {
            scanf("%d", &choice);
            printf("Input =  %d\n", choice);
        } else {
            printf("Timed Out 超时！！！！\n\n");
            return;
        }

        getchar();
        switch (choice) {
            case 1:
                Student_Select();
                break;
            case 2:
                Student_bijiao();
                break;
            case 3:
                return;
                break;
        }
        IO_WriteInfo();
    }
}

int timeout(int seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
    return 1;
}

/*主程序*/

void Student_js() {
    int choice;
    IO_ReadInfo();
    struct pollfd mypoll = {STDIN_FILENO, POLLIN | POLLPRI};
    // Timeout in 5 seconds, reference: https://www.quora.com/How-do-I-put-a-time-limit-to-the-scanf-function

    while (1) {
        /*主菜单*/

        printf("\n------ 学生成绩管理系统------\n");
        printf("1. 增加学生记录\n");
        printf("2. 修改学生记录\n");
        printf("3. 删除学生记录\n");
        printf("4. 按学号查询学生记录\n");
        printf("5. 按总分成绩排序\n");
        printf("6. 按英语成绩排序\n");
        printf("7. 按高数成绩排序\n");
        printf("8. 显示单科高数不及格学生信息\n");
        printf("9. 显示单科英语不及格学生信息\n");
        printf("10. 显示男生或女生平均分\n");
        printf("11. 退出\n");
        printf("请选择(1-11):");
        if (poll(&mypoll, 1, TimeOutMilliSeconds)) {
            scanf("%d", &choice);
            printf("Input =  %d\n", choice);
        } else {
            printf("Timed Out 超时！！！！\n\n");
            return;
        }
        getchar();
        switch (choice) {
            case 1:
                Student_Insert();
                break;
            case 2:
                Student_Modify();
                break;
            case 3:
                Student_Delete();
                break;
            case 4:
                Student_Select();
                break;
            case 5:
                Student_SortBysum();
                Student_Display();
                break;
            case 6:
                Student_SortByMath();
                Student_Display();
                break;
            case 7:
                Student_SortByEnglish();
                Student_Display();
                break;
            case 8:
                Student_No1();
                break;
            case 9:
                Student_No2();
                break;
            case 10:
                averageScoreByGender();
                break;
            case 11:
                return;
        }
        IO_WriteInfo();
    }
}

void main() {
    int choice;
    IO_ReadInfo();
    while (1) {
        printf("1. 教师登录\n");
        printf("2. 学生登录\n");
        printf("请选择(1-2):");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                Student_js();
                break;
            case 2:
                Student_xs();
                break;
        }
        IO_WriteInfo();
    }
}
