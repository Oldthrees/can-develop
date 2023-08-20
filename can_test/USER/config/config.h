#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "stm32f10x.h"

#define WATCH_DOG               1       //���Ź�
#define CONFIG_DATA_ADDR        ((uint32_t)0x08008000)//�������ݴ���

#define         CONFIG_FILE             1       //�����ļ���
#define         MUSIC_FILE              2       //�����ļ���

//�����ļ����е�����
#define         ENTER_INTO_CONFIG_MUSIC                 1       //��������ģʽ����    
#define         ORDER_TRIGGER_MUSIC                     2       //˳�򴥷�ģʽ����  
#define         SAME_TRIGGER_MUSIC                      3       //ͬʱ����ģʽ����  
#define         ENTER_INTO_ORDER_TRIGGER_MUSIC          4       //����˳�򴥷�ģʽ����  
#define         ENTER_INTO_SAME_TRIGGER_MUSIC           5       //����ͬʱ����ģʽ����  
#define         CHOOSE_PORT_NUM_MUSIC                   6       //ѡ������˿�����
#define         PORT_NUM_ONE_MUSIC                      7       //һ���˿�����  
#define         PORT_NUM_TWO_MUSIC                      8       //�����˿�����  
#define         PORT_NUM_THREE_MUSIC                    9       //�����˿�����  
#define         PORT_NUM_FOUR_MUSIC                     10      //�ĸ��˿�����  
#define         PORT_NUM_FIVE_MUSIC                     11      //����˿�����  
#define         PORT_NUM_SIX_MUSIC                      12      //�����˿�����  
#define         PORT_NUM_SEVEN_MUSIC                    13      //�߸��˿�����  
#define         PORT_NUM_EIGHT_MUSIC                    14      //�˸��˿�����
#define         TRIGGER_PORT_IN_ORDER_MUSIC             15      //����˳�򴥷�����˿�����
#define         TRIGGER_ALL_PORT_MUSIC                  16      //�����ж˿����δ�������
#define         FINISH_INPUT_MUSIC                      17      //�����������
#define         CHOOSE_RELAY_JUMP_MUSIC                 18      //ѡ����ش�����̵����Ƿ���������
#define         RELAY_JUMP_MUSIC                        19      //������̵�����������
#define         RELAY_NO_JUMP_MUSIC                     20      //������̵�������������
#define         CHOOSE_MUSIC                            21      //ѡ����ش����󲥷�����
#define         CONFIG_MUSIC_ONE                        22      //����һ
#define         CONFIG_MUSIC_TWO                        23      //���ֶ�
#define         CONFIG_MUSIC_THREE                      24      //������
#define         CONFIG_MUSIC_FOUR                       25      //������
#define         CONFIG_MUSIC_FIVE                       26      //������
#define         CONFIG_MUSIC_SIX                        27      //������
#define         CONFIG_MUSIC_SEVEN                      28      //������
#define         CONFIG_MUSIC_EIGHT                      29      //���ְ�
#define         CONFIG_MUSIC_NONE                       30      //����������
#define         CHOOSE_RELAY_WHEN_TRIGGER_MUSIC         31      //ѡ��̵�����ʱ��������
#define         RELAY_MUSIC_TRIGGER_SAME_MUSIC          32      //�̵���������ͬʱ��������
#define         RELAY_TRIGGER_AFTER_MUSIC               33      //�̵��������ֲ�����Ϻ󴥷�
#define         CONFIG_OK_MUSIC                         34      //�����������
#define         WEICOME_MUSIC                           35      //��ӭ����      
#define         PORT_ONE_MUSIC                          36      //�˿�һ��Ч
#define         PORT_TWO_MUSIC                          37      //�˿ڶ���Ч
#define         PORT_THREE_MUSIC                        38      //�˿�����Ч
#define         PORT_FOUR_MUSIC                         39      //�˿�����Ч
#define         PORT_FIVE_MUSIC                         40      //�˿�����Ч
#define         PORT_SIX_MUSIC                          41      //�˿�����Ч
#define         PORT_SEVEN_MUSIC                        42      //�˿�����Ч
#define         PORT_EIGHT_MUSIC                        43      //�˿ڰ���Ч
#define         EMPTY_MUSIC                             44      //������
#define         CHOOSE_PORT_LIGHT_PATTERN_MUSIC         45      //ѡ��˿ڵ�ģʽ����
#define         PORT_LIGHT_ALWAYS_BRIGHT_MUSIC          46      //�˿ڵƳ�������
#define         PORT_LIGHT_BRIGHT_AFTER_TRIGGER_MUSIC   47      //�˿ڵ��ڶ˿ڴ���ʱ������
#define         PRODUCT_KEY_DOWNLOAD_OK_MUSIC           48      //��Ʒ���к����سɹ�����
#define         PRODUCT_KEY_READ_OK_MUSIC               49      //��Ʒ���кŶ�ȡ�ɹ�����
#define         PORT_NUM_SET_TO_ONE                     50      //�˿������ɹ�����Ϊһ��
#define         PORT_NUM_SET_TO_TWO                     51      //�˿������ɹ�����Ϊ����
#define         PORT_NUM_SET_TO_THREE                   52      //�˿������ɹ�����Ϊ����
#define         PORT_NUM_SET_TO_FOUR                    53      //�˿������ɹ�����Ϊ�ĸ�
#define         PORT_NUM_SET_TO_FIVE                    54      //�˿������ɹ�����Ϊ���
#define         PORT_NUM_SET_TO_SIX                     55      //�˿������ɹ�����Ϊ����
#define         PORT_NUM_SET_TO_SEVEN                   56      //�˿������ɹ�����Ϊ�߸�
#define         PORT_NUM_SET_TO_EIGHT                   57      //�˿������ɹ�����Ϊ�˸�
#define         PORT_NUM_SET_FAIL                       58      //�˿���������ʧ��
//�����ļ����е�����
#define         MUSIC_ONE                               1       //����һ
#define         MUSIC_TWO                               2       //���ֶ�
#define         MUSIC_THREE                             3       //������
#define         MUSIC_FOUR                              4       //������
#define         MUSIC_FIVE                              5       //������
#define         MUSIC_SIX                               6       //������
#define         MUSIC_SEVEN                             7       //������
#define         MUSIC_EIGHT                             8       //���ְ�

extern void config_menu(void);
extern void key_scan(void);//����ɨ��
extern void IWDG_Feed(void);//ι��

extern uint8_t port_num_config(uint8_t key_word[],uint8_t array[]);

extern uint8_t first_password;//˳�򴥷�ģʽ�µĵ�һλ����
extern uint8_t light_show_config;//�˿ڵ���ʾ��״̬  1���˿ڵƳ���  2���˿ڵ��ڶ˿ڴ���ʱ��

extern uint8_t music_play_flag;//�����Ƿ񲥷ŵı�־λ

extern uint8_t port_num;//�˿�����

#endif