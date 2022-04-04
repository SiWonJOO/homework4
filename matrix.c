#include <stdio.h>
#include <stdlib.h>
#include <time.h> // rand 함수를 사용하기 위한 라이브러리 헤더파일 이다.

/* Method Declaration */ 
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [SIWON JOO]]  [2018038045] -----]\n");

    int row, col;
    srand(time(NULL)); // Initialize Matrix함수를 호출할때마다 랜덤한 값을 채우기 위한 함수.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); // 더블 포인터 정수형 변수 선언
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); // 전치행렬이기때문에 행렬 인자값 순서 바꿈.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} // 만약 배열이 비어있다면 -1 리턴

    do{ // 반복문 실행후 조건 만족하면 반복
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col); //row x col 의 행렬 a를 만든다.
            fill_data(matrix_b, row, col); //row x col 의 행렬 b를 만든다.
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); // 행렬a 를 출력하는 함수 호출
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // 행렬b 를 출력하는 함수 호출
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); // 행렬 a와 b를 합하여 출력하는 함수 호출
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // 행렬 a와 b를 빼고난 다음 출력하는 함수 호출
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 a 의 전치행렬인 행렬 t를 생성하는 함수 호출
            print_matrix(matrix_a_t, col, row); // 전치행렬 t를 출력하는 함수 호출
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 a 의 전치행렬인 행렬 t를 생성하는 함수 호출
            multiply_matrix(matrix_a, matrix_a_t, row, col); //행렬 a와 전치행렬 t를 곱하여 출력하는 함수 호출
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // 전치행렬 t 메모리의 할당을 해제해줌.
            free_matrix(matrix_a, row, col); // 행렬 a 메모리의 할당을 해제해줌.
            free_matrix(matrix_b, row, col); // 행렬 b 메모리의 할당을 해제해줌.
            break;
        default: // 정의된 case 가 아닌 다른값을 입력받았을 때
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //한번은 무조건 실행하고 q와 Q 를 입력받았을때 반복문을 탈출하게 된다.

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre coditions*/
    if (row<=0 || col <= 0) // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return NULL;
    }
    int** matrix = (int**) malloc(sizeof(int*)*row); // 더블 포인터 정수형 matrix에 메모리 할당해줌
    for(int r=0; r<row; r++) // 
    {
        matrix[r] = (int *)malloc(sizeof(int)*col); 
    }
    /* Check post conditions */
    if(matrix == NULL) // matrix가 비어있다면
    {
            printf("Memory Allocation Failed\n");
            return NULL;
    }
    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /*Check pre coditions*/
    if (row <= 0 || col <= 0) // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return;// void 형이라 return 값 없음.
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++) // 2차원행렬을 출력하기 위해 2중 for문 사용
    {
        for(int matrix_col = 0; matrix_col<col; matrix_col++)
        {
            printf("%3d ", matrix[matrix_row][matrix_col]); // 3자리 보다 작으면 여백을 추가해서 3자리를 확보해서 출력한다.
        }
            printf("\n");       
    }
      /* Check post conditions */
    if(matrix == NULL) // matrix가 비어있다면
    {
            printf("Memory Allocation Failed\n");
            return; // void 형이라 return 값 없음.
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /*Check pre conditions*/
    if (row <=0 || col <= 0) // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return -1;
    }
    for(int matrix_row=0; matrix_row <row; matrix_row++)
    {
        free(matrix[matrix_row]); // 할당된 메모리를 할당 해제해준다. -deallocation
    }
    free(matrix);
    return 1; //true값 리턴
    // 이미 메모리를 해제 해 주었기 때문에 후처리 검사를 할 필요가 없음.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /*Check pre conditions*/
    if (row <=0||col<=0)  // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col! \n");
    }
    for(int matrix_row=0;matrix_row<row;matrix_row++) // 2차원 행렬에 값을 대입하기 위해 이중 for문 사용
    {
        for(int matrix_col=0;matrix_col<col;matrix_col++)
        {
            matrix[matrix_row][matrix_col] = rand()%20; // 0~19 까지 랜덤한 값을 대입해줌.
        }
    }
    /*Check post conditions*/
    if(matrix==NULL) // matrix가 비어있다면
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row,col);
    /*Check pre conditions*/
    if(row<=0||col<=0) // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return -1;
    }    
    for(int matrix_col=0;matrix_col<col;matrix_col++) // 행렬 A와 B를 합하기 위해 이중 For 문 사용함.
        for(int matrix_row=0;matrix_row<row;matrix_row++)
        {
            matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
        }
    /* Check post conditions*/
    if(matrix_a==NULL || matrix_b == NULL || matrix_sum == NULL) // matrix가 전부 비어있다면
    {
       printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(matrix_sum,row,col); // 행렬의 합을 출력
    free_matrix(matrix_sum,row,col); // 할당된 메모리 해제해줌.
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row,col); 
    /* Check pre conditions */
    if(row <= 0 || col <=0)  // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row <row; matrix_row++) // 행렬 A와 B를 빼기 위해 이중 for 문 사용함. 
        for(int matrix_col=0; matrix_col <col; matrix_col++)
        {
            matrix_sub[matrix_row][matrix_col]= matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
        }
    /* Check post conditions */
    if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) // 이차원 배열중 하나라도 비어있다면
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(matrix_sub,row,col); // 행렬의 차 출력
    free_matrix(matrix_sub,row,col); // 할당된 메모리 해제해줌.

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* Check pre conditions */
    if(row<=0 || col <=0) // row나 col 이 자연수가 아니라면
    {
        printf("Check the size of row and col!\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row<row; matrix_row++) // 2차원 배열이기때문에 이중 for문 사용해줌.
        for(int matrix_col=0;matrix_col<col;matrix_col++)
        {
            matrix_t[matrix_row][matrix_col]=matrix[matrix_col][matrix_row]; // 행과 열의 순서를 바꿔서 matrix_t 에 대입해준다.
        }
    /*Check post conditions*/
    if(matrix == NULL || matrix_t == NULL) // 이차원 배열중 하나라도 비어있다면
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row,row); // 행렬의 곱이기 때문에 ex)2x3 3x2 행렬의 곱을하면 2x2 행렬이 나옴 따라서 row,row 인자를 받음
        /*Check pre conditions*/
        if(row<=0||col<=0)  // row나 col 이 자연수가 아니라면
        {
            printf("Check the size of row and col!\n");
            return -1;
        }
    for(int matrix_a_row=0;matrix_a_row<row;matrix_a_row++) //전치행렬t와 행렬 a의 곱한값을 matrix_axt에 넣어줘야 하기 때문에 3중 for문을 사용하였다.
    {
        for(int matrix_t_row =0; matrix_t_row<row;matrix_t_row++)
        {
            int temp = 0; // 전치행렬 t와 행렬 a를 곱한 값을 받기위해서 temp 변수를 선언해줌
            for(int matrix_col=0; matrix_col<col;matrix_col++) // 
            {
            temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // temp 에 행렬 a와 전치행렬 t를 곱한 값을 넣어줌.
            matrix_axt[matrix_a_row][matrix_t_row] = temp; // temp가 받은 값을 matrix_axt 행렬에 채워준다. 
            }
        }
    }
    if(matrix_t == NULL||matrix_axt == NULL) // matrix가 비어있다면
    {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(matrix_axt,row,row); // 전치행렬 t를 출력해주는 함수호출.
    free_matrix(matrix_axt,row,col); // 할당된 메모리 해제해줌.
    return 1;
}

