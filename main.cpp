#include <stdio.h>
#include <stdint.h>

void first_task()
{
    const uint32_t result_size = 6;
    int32_t result[result_size];
    int32_t argument = 4;
    __asm
    {
        mov ebx, 4 ; � ebx ����� ��������� �������� ��������� ������� X, ������������ �� 4 � ����� 3
        mov ecx, 0 ; � ecx ����� ��������� ������� �����, ��� �������� ���� ��� �� ��������� ������ 6 �������� �������

        loop_start: ; ������ �����
        cmp ecx, 6
        je loop_end ; ��������� ����, ���� ��� ���� ��������� 6 ��������

        ; ������� ������ ������ = (3 * X^2 + 20)
        mov eax, ebx ; ��������� ������� �������� ��������� X
        mul eax ; ��������� X ^ 2
        mov edx, 3
        mul edx ;  ��������� 3 * X^2
        add eax, 20 ; ��������� 3 * X^2 + 20
        mov edi, eax ; ��������� �������� ������ ������ � edi ��� ������������� � ��������� �������� �������

        ; ������� ������ ������ = (2500*X - 8)
        mov eax, ebx ; ��������� ������� �������� ��������� X
        mov edx, 2500
        mul edx ; ��������� 2500 * X
        sub eax, 8 ; ��������� 2500*X - 8

        ; ��������� �������� �������
        idiv edi ; ����� �������� ������ ������ �� �������� ������
        shr edi, 1
        cmp edi, edx ; ���������� ������� �� ������� � ��������� ��������
        adc eax, 0 ; � ����������� �� ���������� ��������� ��������� ���������� �������� � ���������� ��������������

        mov DWORD PTR [result + ecx * 4], eax ; ��������� ��������� � ������ ��� ��������������� ��������

        add ebx, 3 ; ��������� ��� ��������� � �������� �������� X
        inc ecx
        jmp loop_start ; ����������� �������� �������� ����� �� 1 � ��������� � ������ �����

        loop_end:
    } 
    for (uint32_t i = 0; i < result_size; i++)
    {
        printf("%u: %d\n", i + 1, result[i]);
    }
}

void second_task()
{
    int32_t result;
    __asm
    {
        mov ecx, 0 ; � ecx ����� ��������� �������� ��������� X
        loop_start:

        ; ������� �������� ������� ��������� = 7 * X^2
        mov eax, ecx ; ��������� ������� �������� ��������� X
        mul eax ; ��������� X ^ 2
        mov edx, 7
        mul edx ; ��������� 7 * X^2
        mov edi, eax ; ��������� �������� ������� ��������� � edi ��� ������������� � ��������� �������� ��������

        ; ��������� �������� ����� ������� � �������� ��������� = 25*X - 27
        mov eax, ecx ; ��������� ������� �������� ��������� X
        mov edx, 25
        mul edx ; ��������� 25 * X
        sub eax, 27 ; ��������� 25*X - 27

        add eax, edi ; ��������� ����� ����� ���������

        cmp eax, 3000
        jg loop_end ; ���� ���������� �������� ������ 3000 ����������� ����
        inc ecx
        jmp loop_start ; � ��������� ������ ����������� �������� X �� 1 � ���������� ����

        loop_end:
        mov [result], ecx ; � ����� ���������� ������� �������� ��������� X � ������
    } 
    printf("%d\n", result);
}

void third_task()
{
    int32_t result;
    int32_t source[10] = { 0, 0b1, 0b10, 0b11, 0b100, 0b101, 0b110, 0b111, 0b1000, 0b1001 };
    __asm
    {
        mov eax, 0 ; � eax ����� ��������� ���������� ��������� �����
        lea ebx, source ; � ebx ����� ��������� ����� �������, ������� �� �����������
        mov ecx, 0 ; � ecx ����� ��������� ������ �������� �������� �������
        loop_start: ; ������ ��������� �����, ������� ��������� ���������� ��������� ����� � ������ �������� �������

        mov edi, [ebx + ecx * 4] ; ��������� ������� ������� �������
        inner_loop_start: ; ������ ����������� �����, ������� ������� ���������� ��������� ����� � ������� �������� �������
        cmp edi, 0
        je inner_loop_end ; ���� ������� ������� ������� ����� 0, �� �� ������� �� ����������� �����

        mov esi, edi
        and esi, 1 ; � ������� ����������� � ��������� �������� ������ ������� ���� �������� �������� ������� = 0 ��� 1
        add eax, esi ; ��������� ���������� �������� 0 ��� 1 � �������� ��������� �����
        shr edi, 1 ; �������� �������� �������� �������� ������� ����� �� 1 ���
        jmp inner_loop_start ; ���������� ����
        inner_loop_end:

        inc ecx ; ����������� ������ �������� �������� ������� �� 1
        cmp ecx, 10
        jne loop_start ; ����������� ����, ���� �� ����������� ��� 10 ��������� �������
        mov DWORD PTR [result], eax ; ��������� ��������� � ������
    } 
    printf("%d\n", result);
}

int main()
{
    printf("1st:\n");
    first_task();
    printf("\n");

    printf("2nd:\n");
    second_task();
    printf("\n");

    printf("3rd:\n");
    third_task();
    printf("\n");
}

