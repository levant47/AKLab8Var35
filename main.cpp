#include <stdio.h>
#include <stdint.h>

void first_task()
{
    const uint32_t result_size = 6;
    int32_t result[result_size];
    int32_t argument = 4;
    __asm
    {
        mov ebx, 4
        mov ecx, 0
        loop_start:
        cmp ecx, 6
        je loop_end

        ; second parentheses
        mov eax, ebx
        mul eax
        mov edx, 3
        mul edx
        add eax, 20
        mov edi, eax

        ; first parentheses
        mov eax, ebx
        mov edx, 2500
        mul edx
        sub eax, 8

        ; final divsion
        mov edx, 0
        idiv edi
        shr edi, 1
        cmp edi, edx
        adc eax, 0
        mov DWORD PTR [result + ecx * 4], eax

        add ebx, 3
        inc ecx
        jmp loop_start
        loop_end:
    } 
    for (uint32_t i = 0; i < result_size; i++)
    {
        printf("%u: %d\n", i, result[i]);
    }
}

void second_task()
{
    int32_t result;
    __asm
    {
        mov ecx, 0
        loop_start:
        inc ecx

        ; first minome
        mov eax, ecx
        mul eax
        mov edx, 7
        mul edx
        mov edi, eax

        ; second and third minomes
        mov eax, ecx
        mov edx, 25
        mul edx
        sub eax, 27

        add eax, edi

        cmp eax, 3000
        jle loop_start
        mov [result], ecx
    } 
    printf("%d\n", result);
}

void third_task()
{
    int32_t result;
    int32_t source[10]{ 0, 0b1, 0b10, 0b11, 0b100, 0b101, 0b110, 0b111, 0b1000, 0b1001 };
    __asm
    {
        mov eax, 0
        lea ebx, source
        mov ecx, 0
        loop_start:

        mov edi, [ebx + ecx * 4]
        inner_loop_start:
        cmp edi, 0
        je inner_loop_end
        mov esi, edi
        and esi, 1
        add eax, esi
        shr edi, 1
        jmp inner_loop_start
        inner_loop_end:

        inc ecx
        cmp ecx, 10
        jne loop_start
        mov DWORD PTR [result], eax
    } 
    printf("%d\n", result);
}

int main()
{
    first_task();
    second_task();
    third_task();
}

