#include<stdio.h>
#include <stdlib.h>
#include<time.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10
#define PROB_MAX 90
#define AGGRO_MIN 0 
#define AGGRO_MAX 5


#define MOVE_LEFT 1
#define MOVE_STAY 0


#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2


#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int trainlength, percentileprobability, mStamina;
int Citizen, Zombie, Madong;
int CitizenAggro = 1, MadongAggro = 1;
int turn = 1;
int ZombiePulled = 0;



int main(void) {
    srand((unsigned int)time(NULL));


    printf("���õ� �ٸ� ���� ���� ���̾���\n");
    printf("Ư���� �� ���� �Ѱᰰ�� ��.. ���� ����ޱ�?  \n");
    printf("������ ������ ���ο� ���� ����� ��� ������ �ϴ� ���̾��µ�..\n");
    printf("��� ������ ���ڱ� ���Ҹ��� ����´�.. �̷��� �ٷ� ���� ����°� ������ �ʾҴµ�..\n");
    printf("�ϴ� ����ġ�� ����..!\n");
    printf("--------- Start ---------\n");

    int trainlength, percentileprobability, mStamina;
    printf("���� ���̸� �Է����ּ��� (%d-%d)\n", 15, 50);
    scanf_s("%d", &trainlength);
    printf("Ȯ���� �Է����ּ���(%d-%d)\n", 10, 90);
    scanf_s("%d", &percentileprobability);
    printf("������ ü���� �Է����ּ���(%d-%d)\n", 0, 5);
    scanf_s("%d", &mStamina);

    printf("trainlength : %d meters\n", trainlength);
    printf("percentileprobability : %d%%\n", percentileprobability);
    printf("������ ü�� : %d%%\n", mStamina);

    printf("���� ���� :\n");
    for (int i = 0; i < trainlength; ++i) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < trainlength; ++i) {
        if (i == trainlength - 6) {
            printf("C");
        }
        else if (i == trainlength - 3) {
            printf("Z");
        }
        else if (i == trainlength - 2) {
            printf("M");
        }
        else {
            if (i == 0 || i == trainlength - 1) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
    }
    printf("\n");


    for (int i = 0; i < trainlength; ++i) {
        printf("#");
    } printf("\n");


    Citizen = trainlength - 6;
    Zombie = trainlength - 3;
    Madong = trainlength - 2;
    turn = 1;

    while (1) {
        if (Citizen == 1) {
            printf("----------Success----------\n");
            break;
        }if (mStamina <= STM_MIN) {
            printf("----------GAME OVER!----------");
            printf("Madonseok has been defeated.\n");
            break;
        } turn++;

        //�ù�        
        if (Citizen > 1) {
            int randomNum = rand() % 100;
            if (randomNum < (100 - percentileprobability)) {
                Citizen--;
                if (CitizenAggro < AGGRO_MAX) {
                    CitizenAggro++;
                }
                printf("Citizen : %d -> %d\n", Citizen + 1, Citizen);
            }
            else {
                if (CitizenAggro > AGGRO_MIN) {
                    CitizenAggro--;
                }
                printf("Citizen:stay %d\n", Citizen);
            }
        }

        //����
        if (ZombiePulled) {
            printf("Zombie was pulled and cannot move this.\n");
            ZombiePulled = 0;
        }
        else if (turn % 2 == 0) {
            int target = Citizen;
            if (MadongAggro > CitizenAggro) {
                target = Madong;
            }
            if (target == Citizen && Citizen == Zombie + 1) {
                printf("Zombie: stay %d\n", Zombie);
            }
            else if (target == Madong && Madong == Zombie + 1) {
                printf("Zombie: stay %d\n", Zombie);
            }
            else {
                Zombie--;
                printf("Zombie: %d -> %d\n", Zombie + 1, Zombie);
            }
        }
        else {
            printf("Zombie caanot move this turn.\n");
        }
        for (int i = 0; i < trainlength; ++i) {
            printf("#");
        }
        printf("\n");

        for (int i = 0; i < trainlength; ++i) {
            if (i == Citizen) {
                printf("C");
            }
            else if (i == Zombie) {
                printf("Z");
            }
            else if (i == Madong) {
                printf("M");
            }
            else {
                if (i == 0 || i == trainlength - 1) {
                    printf("#");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");


        for (int i = 0; i < trainlength; ++i) {
            printf("#");
        } printf("\n");

        //������
        int move;
        do {
            printf("Madongseok (0:stay, 1:Left) : ");
            scanf_s("%d", &move);
        } while (move != MOVE_STAY && move != MOVE_LEFT);
        if (move == MOVE_LEFT) {
            Madong--;
            if (MadongAggro < AGGRO_MAX) {
                MadongAggro++;
            }
        }
        else {
            if (MadongAggro > AGGRO_MIN) {
                MadongAggro--;
            }
        }
        printf("Madongseok : %d(%d, %d)\n", Madong, MadongAggro, mStamina);
    }
    //�ൿ
    //�ù�
    if (Citizen == 1) {
        printf("----------Success----------\n");
        exit(0);
    }

    //����
    if (Zombie == Citizen + 1 && Zombie == Madong + 1) {
        if (CitizenAggro > MadongAggro) {
            printf("----------GAME OVER!----------\n");
            printf("Citizen has been attacked by a zombie.\n");
            exit(0);
        }
        else {
            printf("Zombie attaks Madongseok!\n");
            mStamina--;
            if (mStamina <= STM_MIN) {
                printf("--------- GAME OVER!----------\n");
                printf("MAdongseok has been defeated.\n");
                exit(0);
            }
        }
    }
    //������
    int acting;
    do {
        if (Zombie == Madong + 1) {
            printf("Madongseok (0 : Rest, 1: Provoke, 2: Pull):  ");
            scanf_s("%d", &acting);
        }
        else {
            printf("Madongseok (0: Rest, 1: Provoke):   ");
            scanf_s("%d", &acting);
        }
        if (Zombie == Madong + 1) {
            if (acting == ACTION_REST || acting == ACTION_PROVOKE || acting == ACTION_PULL) {
                break;
            }
        }
        else {
            if (acting == ACTION_REST || acting == ACTION_PROVOKE) {
                break;
            }
        }
    } while (1);

    if (acting == ACTION_REST) {
        if (MadongAggro > AGGRO_MIN) {
            MadongAggro--;
        }
        if (mStamina < STM_MAX) {
            mStamina++;
        }
    }
    else if (acting == ACTION_PROVOKE) {
        MadongAggro = AGGRO_MAX;
    }
    else if (acting == ACTION_PULL) {
        if (MadongAggro < AGGRO_MAX) {
            MadongAggro += 2;
        }
        mStamina--;
        int randomNum = rand() % 100;
        if (randomNum < (100 - percentileprobability)) {
            ZombiePulled = 1;
            printf("Madongseok pulled the zombie...Next turn, it can't move.\n");
        }
        else {
            printf("Madongseok failed to pull the zombie\n");
        }
    }

    printf("Madongseok : %d (%d, %d)\n", Madong, MadongAggro, mStamina);

    return 0;
}