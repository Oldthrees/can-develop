#include <config.h>
#include <string.h>
#include <delay.h>

uint16_t key_timer[8]={0};
uint16_t config_key_timer = 0;

uint8_t config_input_times_up_flag[8] = {0};
uint8_t long_key_times_up_flag,short_key_times_up_flag;

uint8_t config_input[8];//���ð���������
uint8_t config_mode = 0;//����ģʽ

uint8_t password_num = 0;

uint8_t config_key_long = 0,config_key_short = 0;//���ð��������Ͷ̰�

uint8_t password_num_count;//��������������ж���������λ���Ƿ񵽴�

uint8_t first_password = 0;//˳�򴥷�ģʽ�µĵ�һλ����

uint8_t relay_config_state = 0;//�̵��������Ƿ�����
uint8_t music_config_num = 0;//�������õı��
uint8_t relay_strike_time = 0;//�̵�������ʱ��
uint8_t light_show_config = 0;//�˿ڵ���ʾ��״̬  1���˿ڵƳ���  2���˿ڵ��ڶ˿ڴ���ʱ��

extern uint8_t password[32];

extern void play_music(uint8_t file,uint8_t num);
void key_scan(void)//����ɨ��
{
    //���ð������
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0 && long_key_times_up_flag == 0)
    {
        config_key_timer++;
        if(config_key_timer > 1000)
        {
            config_key_long = 1;
            long_key_times_up_flag = 1;
        }
        else if(config_key_timer > 50)
        {
            short_key_times_up_flag = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1 && short_key_times_up_flag == 1 && long_key_times_up_flag == 0)
    {
        config_key_short = 1;
        short_key_times_up_flag = 0;
        config_key_timer = 0;
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1)
    {
        config_key_timer = 0;
        short_key_times_up_flag = 0;
        long_key_times_up_flag = 0;
    }
    
    //1
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1 && config_input_times_up_flag[0] == 0)
    {
        key_timer[0]++;
        if(key_timer[0] > 30)
        {
            config_input[0] = 1;
            config_input_times_up_flag[0] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 0)
    {
        key_timer[0] = 0;
        config_input_times_up_flag[0] = 0;
    }
    
    //2
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15) == 1 && config_input_times_up_flag[1] == 0 && port_num > 1)
    {
        key_timer[1]++;
        if(key_timer[1] > 30)
        {
            config_input[1] = 1;
            config_input_times_up_flag[1] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15) == 0)
    {
        key_timer[1] = 0;
        config_input_times_up_flag[1] = 0;
    }
    
    //3
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 1 && config_input_times_up_flag[2] == 0 && port_num > 2)
    {
        key_timer[2]++;
        if(key_timer[2] > 30)
        {
            config_input[2] = 1;
            config_input_times_up_flag[2] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0)
    {
        key_timer[2] = 0;
        config_input_times_up_flag[2] = 0;
    }
    
    //4
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 1 && config_input_times_up_flag[3] == 0 && port_num > 3)
    {
        key_timer[3]++;
        if(key_timer[3] > 30)
        {
            config_input[3] = 1;
            config_input_times_up_flag[3] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0)
    {
        key_timer[3] = 0;
        config_input_times_up_flag[3] = 0;
    }
    
    //5
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1 && config_input_times_up_flag[4] == 0 && port_num > 4)
    {
        key_timer[4]++;
        if(key_timer[4] > 30)
        {
            config_input[4] = 1;
            config_input_times_up_flag[4] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 0)
    {
        key_timer[4] = 0;
        config_input_times_up_flag[4] = 0;
    }
    
    //6
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1 && config_input_times_up_flag[5] == 0 && port_num > 5)
    {
        key_timer[5]++;
        if(key_timer[5] > 30)
        {
            config_input[5] = 1;
            config_input_times_up_flag[5] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
    {
        key_timer[5] = 0;
        config_input_times_up_flag[5] = 0;
    }
    
    //7
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1 && config_input_times_up_flag[6] == 0 && port_num > 6)
    {
        key_timer[6]++;
        if(key_timer[6] > 30)
        {
            config_input[6] = 1;
            config_input_times_up_flag[6] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0)
    {
        key_timer[6] = 0;
        config_input_times_up_flag[6] = 0;
    }
    
    //8
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 1 && config_input_times_up_flag[7] == 0 && port_num > 7)
    {
        key_timer[7]++;
        if(key_timer[7] > 30)
        {
            config_input[7] = 1;
            config_input_times_up_flag[7] = 1;
        }
    }
    else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
    {
        key_timer[7] = 0;
        config_input_times_up_flag[7] = 0;
    }
}

void config_data_to_flash(void)
{
    uint8_t data[64] = {0};
    uint32_t Address = 0;
    unsigned char *data_para;
    uint8_t same_password_num = 0;//������ĵ�һλ��ʼ�������͵�һλ������ͬ�����������
    
    memset(data,0,64);//��������
    data[0] = 1;//����ʹ��
    data[1] = config_mode;//����ģʽ
    data[2] = relay_config_state;//�̵����Ƿ�����
    data[3] = music_config_num;//�������ֱ��
    data[4] = relay_strike_time;//�̵�������ʱ��
    if(config_mode == 1)//˳�򴥷�ģʽ
    {
        first_password = password[0];
        for(uint8_t i=0;i<32;i++)
        {
            if(password[i] == first_password)
            {
                same_password_num++;
            }
            else
            {
                break;
            }
        }
        data[5] = first_password;//��һλ����
        data[6] = same_password_num;//������ĵ�һλ��ʼ�������͵�һλ������ͬ�����������
    }
    data[7] = password_num_count;//˳��ģʽ����������
    data[8] = light_show_config;//�˿ڵ���ʾ��״̬  1���˿ڵƳ���  2���˿ڵ��ڶ˿ڴ���ʱ��

    memcpy(data + 32,password,32);

    //���������flash��
    data_para = data;
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    FLASH_ErasePage(CONFIG_DATA_ADDR);

    Address = CONFIG_DATA_ADDR;

    for(uint8_t k=0;k<32;k++)
    {
        FLASH_ProgramHalfWord(Address,*((uint16_t*)data_para));
        Address += 2;
        data_para += 2;
    }
    FLASH_Lock();
    /****************************/
}

void config_menu(void)
{
    if(config_key_long == 1)//��������ģʽ
    {
        //������ʼ��
        password_num_count = 0;
        
        play_music(CONFIG_FILE,ENTER_INTO_CONFIG_MUSIC);//���Ž�������ģʽ
        delay_ms(50);//ȷ�����ֲ�����
        while(!music_play_flag)//�ȴ����ֲ������
        {
#if WATCH_DOG
            IWDG_Feed();//ι��
#endif
        }
        
        memset(config_input,0,8);//����״̬����
        config_key_long = 0;
        config_key_short = 0;
        uint8_t music_num = 0;
        uint8_t config_num = 0;
        
        while(1)
        {
            if(config_key_short == 1)//ѡ������ģʽ
            {
                switch(music_num)
                {
                    case 0:play_music(CONFIG_FILE,ORDER_TRIGGER_MUSIC);config_num = 0;break;
                    case 1:play_music(CONFIG_FILE,SAME_TRIGGER_MUSIC); config_num = 1;break;
                }
                music_num++;
                if(music_num > 1)music_num = 0;
                config_key_short = 0;
            }
            
            if(config_key_long == 1)//����Ҫ���õ�ģʽ
            {   
                if(config_num == 0)
                {
                  play_music(CONFIG_FILE,ENTER_INTO_ORDER_TRIGGER_MUSIC);
                  delay_ms(50);//ȷ�����ֲ�����
                  while(!music_play_flag)//�ȴ����ֲ������
                  {
#if WATCH_DOG
                        IWDG_Feed();//ι��
#endif
                  }
                  config_mode = 1;//˳�򴥷�ģʽ
                }
                else if(config_num == 1)
                {
                  play_music(CONFIG_FILE,ENTER_INTO_SAME_TRIGGER_MUSIC);
                  delay_ms(50);//ȷ�����ֲ�����
                  while(!music_play_flag)//�ȴ����ֲ������
                  {
#if WATCH_DOG
                        IWDG_Feed();//ι��
#endif
                  }
                  play_music(CONFIG_FILE,CHOOSE_PORT_NUM_MUSIC);//��ѡ������˿�����
                  config_mode = 2;//ͬʱ����ģʽ
                }
                
                config_key_long = 0;
                config_key_short = 0;
                music_num = 0;
                config_num = 0;
                while(1)
                {
                    if(config_mode == 2)//ͬʱ����ģʽ
                    {
                        if(config_key_short == 1)//ѡ������ڵ�����
                        {
                            switch(music_num)
                            {
                                case 0:play_music(CONFIG_FILE,PORT_NUM_ONE_MUSIC);  config_num = 1;break;
                                case 1:play_music(CONFIG_FILE,PORT_NUM_TWO_MUSIC);  config_num = 2;break;
                                case 2:play_music(CONFIG_FILE,PORT_NUM_THREE_MUSIC);config_num = 3;break;
                                case 3:play_music(CONFIG_FILE,PORT_NUM_FOUR_MUSIC); config_num = 4;break;
                                case 4:play_music(CONFIG_FILE,PORT_NUM_FIVE_MUSIC); config_num = 5;break;
                                case 5:play_music(CONFIG_FILE,PORT_NUM_SIX_MUSIC);  config_num = 6;break;
                                case 6:play_music(CONFIG_FILE,PORT_NUM_SEVEN_MUSIC);config_num = 7;break;
                                case 7:play_music(CONFIG_FILE,PORT_NUM_EIGHT_MUSIC);config_num = 8;break;
                            }
                            music_num++;
                            if(music_num > 7)music_num = 0;
                            config_key_short = 0;
                        }
                    }
                    
                    if(config_key_long == 1 || config_mode == 1)//˳�򴥷�ģʽ����ͬʱ����ģʽѡ��ö˿��Ժ�
                    {
                        config_key_long = 0;
                        if(config_mode == 1)//˳�򴥷�ģʽ
                        {
                            play_music(CONFIG_FILE,TRIGGER_PORT_IN_ORDER_MUSIC);//�밴��˳�򴥷�����˿�
                            delay_ms(50);//ȷ�����ֲ�����
                            while(!music_play_flag)//�ȴ����ֲ������
                            {
#if WATCH_DOG
                                IWDG_Feed();//ι��
#endif
                            }
                            memset(password,0,32);//��������
                            memset(config_input,0,8);//����Ķ˿�����
                            while(1)
                            {
                                if(config_input[0] == 1)
                                {
                                    password[password_num_count] = 1;
                                    config_input[0] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_ONE_MUSIC);
                                }
                                else if(config_input[1] == 1)
                                {
                                    password[password_num_count] = 2;
                                    config_input[1] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_TWO_MUSIC);
                                }
                                else if(config_input[2] == 1)
                                {
                                    password[password_num_count] = 3;
                                    config_input[2] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_THREE_MUSIC);
                                }
                                else if(config_input[3] == 1)
                                {
                                    password[password_num_count] = 4;
                                    config_input[3] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_FOUR_MUSIC);
                                }
                                else if(config_input[4] == 1)
                                {
                                    password[password_num_count] = 5;
                                    config_input[4] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_FIVE_MUSIC);
                                }
                                else if(config_input[5] == 1)
                                {
                                    password[password_num_count] = 6;
                                    config_input[5] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_SIX_MUSIC);
                                }
                                else if(config_input[6] == 1)
                                {
                                    password[password_num_count] = 7;
                                    config_input[6] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_SEVEN_MUSIC);
                                }
                                else if(config_input[7] == 1)
                                {
                                    password[password_num_count] = 8;
                                    config_input[7] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_EIGHT_MUSIC);
                                }
                                
                                if(config_key_long == 1 || password_num_count == 32)//�û�ȷ��������ɻ�������ﵽ32λʱ
                                {
                                    config_key_long = 0;
                                    play_music(CONFIG_FILE,FINISH_INPUT_MUSIC);//�������
                                    delay_ms(50);//ȷ�����ֲ�����
                                    while(!music_play_flag)//�ȴ����ֲ������
                                    {
#if WATCH_DOG
                                        IWDG_Feed();//ι��
#endif
                                    }
                                    break;
                                }
#if WATCH_DOG
                                IWDG_Feed();//ι��
#endif
                            }
                        }
                        else if(config_mode == 2)//ͬʱ����ģʽ
                        {
                            play_music(CONFIG_FILE,TRIGGER_ALL_PORT_MUSIC);//�뽫��������˿����δ���
                            delay_ms(50);//ȷ�����ֲ�����
                            while(!music_play_flag)//�ȴ����ֲ������
                            {
#if WATCH_DOG
                                IWDG_Feed();//ι��
#endif
                            }
                            password_num = config_num;
                            memset(password,0x01,32);//��������
                            while(1)
                            {
                                if(config_input[0] == 1 && password[0] == 0x01)
                                {
                                    password[0] = 0;
                                    config_input[0] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_ONE_MUSIC);
                                }
                                else if(config_input[1] == 1 && password[1] == 0x01)
                                {
                                    password[1] = 0;
                                    config_input[1] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_TWO_MUSIC);
                                }
                                else if(config_input[2] == 1 && password[2] == 0x01)
                                {
                                    password[2] = 0;
                                    config_input[2] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_THREE_MUSIC);
                                }
                                else if(config_input[3] == 1 && password[3] == 0x01)
                                {
                                    password[3] = 0;
                                    config_input[3] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_FOUR_MUSIC);
                                }
                                else if(config_input[4] == 1 && password[4] == 0x01)
                                {
                                    password[4] = 0;
                                    config_input[4] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_FIVE_MUSIC);
                                }
                                else if(config_input[5] == 1 && password[5] == 0x01)
                                {
                                    password[5] = 0;
                                    config_input[5] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_SIX_MUSIC);
                                }
                                else if(config_input[6] == 1 && password[6] == 0x01)
                                {
                                    password[6] = 0;
                                    config_input[6] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_SEVEN_MUSIC);
                                }
                                else if(config_input[7] == 1 && password[7] == 0x01)
                                {
                                    password[7] = 0;
                                    config_input[7] = 0;
                                    password_num_count++;
                                    play_music(CONFIG_FILE,PORT_EIGHT_MUSIC);
                                }
                                
                                if(password_num_count == password_num)
                                {
                                    play_music(CONFIG_FILE,FINISH_INPUT_MUSIC);//�������
                                    delay_ms(50);//ȷ�����ֲ�����
                                    while(!music_play_flag)//�ȴ����ֲ������
                                    {
#if WATCH_DOG
                                        IWDG_Feed();//ι��
#endif
                                    }
                                    password_num_count = 0;
                                    password_num = 0;
                                    break;
                                }
#if WATCH_DOG
                                IWDG_Feed();//ι��
#endif
                            }
                        }
                        play_music(CONFIG_FILE,CHOOSE_RELAY_JUMP_MUSIC);//��ѡ����ش�����̵����Ƿ�����
                        delay_ms(50);//ȷ�����ֲ�����
                        while(!music_play_flag)//�ȴ����ֲ������
                        {
#if WATCH_DOG
                            IWDG_Feed();//ι��
#endif
                        }
                        music_num = 0;
                        config_key_short = 0;
                        while(1)
                        {
                            if(config_key_short == 1)//ѡ���Ƿ񴥷��̵���
                            {
                                switch(music_num)
                                {
                                    case 0:play_music(CONFIG_FILE,RELAY_JUMP_MUSIC);    relay_config_state = 1;break;
                                    case 1:play_music(CONFIG_FILE,RELAY_NO_JUMP_MUSIC); relay_config_state = 2;break;
                                }
                                music_num++;
                                if(music_num > 1)music_num = 0;
                                config_key_short = 0;
                            }
                            if(config_key_long == 1)//����ѡ�����ֲ���
                            {
                                config_key_long = 0;
                                play_music(CONFIG_FILE,CHOOSE_MUSIC);//��ѡ�񲥷�����
                                delay_ms(50);//ȷ�����ֲ�����
                                while(!music_play_flag)//�ȴ����ֲ������
                                {
#if WATCH_DOG
                                    IWDG_Feed();//ι��
#endif 
                                }
                                music_num = 1;
                                config_key_short = 0;
                                while(1)
                                {
                                    if(config_key_short == 1)//ѡ�����ֱ��
                                    {
                                        switch(music_num)
                                        {
                                            case 1:play_music(CONFIG_FILE,CONFIG_MUSIC_ONE);   music_config_num = 1;break;
                                            case 2:play_music(CONFIG_FILE,CONFIG_MUSIC_TWO);   music_config_num = 2;break;
                                            case 3:play_music(CONFIG_FILE,CONFIG_MUSIC_THREE); music_config_num = 3;break;
                                            case 4:play_music(CONFIG_FILE,CONFIG_MUSIC_FOUR);  music_config_num = 4;break;
                                            case 5:play_music(CONFIG_FILE,CONFIG_MUSIC_FIVE);  music_config_num = 5;break;
                                            case 6:play_music(CONFIG_FILE,CONFIG_MUSIC_SIX);   music_config_num = 6;break;
                                            case 7:play_music(CONFIG_FILE,CONFIG_MUSIC_SEVEN); music_config_num = 7;break;
                                            case 8:play_music(CONFIG_FILE,CONFIG_MUSIC_EIGHT); music_config_num = 8;break;
                                            case 9:play_music(CONFIG_FILE,CONFIG_MUSIC_NONE);  music_config_num = 9;break;
                                        }
                                        music_num++;
                                        if(music_num > 9)music_num = 1;
                                        config_key_short = 0;
                                    }
                                    if(config_key_long == 1)//����ѡ����ɻ����������
                                    {
                                        config_key_long = 0;
                                        if((relay_config_state == 1 && music_config_num == 9) || (relay_config_state == 2 && music_config_num != 9))//ֻѡ���˼̵�����������
                                        {
                                            play_music(CONFIG_FILE,CHOOSE_PORT_LIGHT_PATTERN_MUSIC);//��ѡ��˿ڵ�ģʽ
                                            delay_ms(50);//ȷ�����ֲ�����
                                            while(!music_play_flag)//�ȴ����ֲ������
                                            {
#if WATCH_DOG
                                                IWDG_Feed();//ι��
#endif
                                            }
                                            music_num = 0;
                                            config_key_short = 0;
                                            while(1)
                                            {
                                                if(config_key_short == 1)//ѡ��˿ڵ�ģʽ
                                                {
                                                    switch(music_num)
                                                    {
                                                        case 0:play_music(CONFIG_FILE,PORT_LIGHT_ALWAYS_BRIGHT_MUSIC);          light_show_config = 1;break;
                                                        case 1:play_music(CONFIG_FILE,PORT_LIGHT_BRIGHT_AFTER_TRIGGER_MUSIC);   light_show_config = 2;break;
                                                    }
                                                    music_num++;
                                                    if(music_num > 1)music_num = 0;
                                                    config_key_short = 0;
                                                }
                                                if(config_key_long == 1)//�˿ڵ�ģʽѡ�����
                                                {
                                                    config_key_long = 0;
                                                    
                                                    config_data_to_flash();//���û����úõ���Ϣ����flash��
                                                    
                                                    play_music(CONFIG_FILE,CONFIG_OK_MUSIC);//�������
                                                    delay_ms(50);//ȷ�����ֲ�����
                                                    while(!music_play_flag)//�ȴ����ֲ������
                                                    {
#if WATCH_DOG
                                                        IWDG_Feed();//ι��
#endif
                                                    }
                                                    while(1);//�豸����
                                                }
#if WATCH_DOG
                                                IWDG_Feed();//ι��
#endif
                                            }
                                        }
                                        else if(relay_config_state == 1 && music_config_num != 9)//�̵��������ֶ�ѡ����
                                        {
                                            play_music(CONFIG_FILE,CHOOSE_RELAY_WHEN_TRIGGER_MUSIC);//��ѡ��̵�����ʱ����
                                            delay_ms(50);//ȷ�����ֲ�����
                                            while(!music_play_flag)//�ȴ����ֲ������
                                            {
#if WATCH_DOG
                                                IWDG_Feed();//ι��
#endif       
                                            }
                                            music_num = 0;
                                            config_key_short = 0;
                                            while(1)
                                            {
                                                if(config_key_short == 1)//ѡ��̵�����ʱ����
                                                {
                                                    switch(music_num)
                                                    {
                                                        case 0:play_music(CONFIG_FILE,RELAY_MUSIC_TRIGGER_SAME_MUSIC);  relay_strike_time = 1;break;
                                                        case 1:play_music(CONFIG_FILE,RELAY_TRIGGER_AFTER_MUSIC);       relay_strike_time = 2;break;
                                                    }
                                                    music_num++;
                                                    if(music_num > 1)music_num = 0;
                                                    config_key_short = 0;
                                                }
                                                if(config_key_long == 1)//�̵�������ʱ��ѡ�����
                                                {
                                                    config_key_long = 0;
                                                    
                                                    play_music(CONFIG_FILE,CHOOSE_PORT_LIGHT_PATTERN_MUSIC);//��ѡ��˿ڵ�ģʽ
                                                    delay_ms(50);//ȷ�����ֲ�����
                                                    while(!music_play_flag)//�ȴ����ֲ������
                                                    {
#if WATCH_DOG
                                                        IWDG_Feed();//ι��
#endif       
                                                    }
                                                    music_num = 0;
                                                    while(1)
                                                    {
                                                        if(config_key_short == 1)//ѡ��˿ڵ�ģʽ
                                                        {
                                                            switch(music_num)
                                                            {
                                                                case 0:play_music(CONFIG_FILE,PORT_LIGHT_ALWAYS_BRIGHT_MUSIC);          light_show_config = 1;break;
                                                                case 1:play_music(CONFIG_FILE,PORT_LIGHT_BRIGHT_AFTER_TRIGGER_MUSIC);   light_show_config = 2;break;
                                                            }
                                                            music_num++;
                                                            if(music_num > 1)music_num = 0;
                                                            config_key_short = 0;
                                                        }
                                                        if(config_key_long == 1)//�˿ڵ�ģʽѡ�����
                                                        {
                                                            config_key_long = 0;
                                                            
                                                            config_data_to_flash();//���û����úõ���Ϣ����flash��
                                                            
                                                            play_music(CONFIG_FILE,CONFIG_OK_MUSIC);//�������
                                                            delay_ms(50);//ȷ�����ֲ�����
                                                            while(!music_play_flag)//�ȴ����ֲ������
                                                            {
#if WATCH_DOG
                                                                IWDG_Feed();//ι��
#endif       
                                                            }
                                                            while(1);//�豸����
                                                        }
#if WATCH_DOG
                                                        IWDG_Feed();//ι��
#endif       
                                                    }
                                                }
#if WATCH_DOG
                                                IWDG_Feed();//ι��
#endif
                                            }
                                        }
                                    }
#if WATCH_DOG
                                    IWDG_Feed();//ι��
#endif
                                }
                            }
#if WATCH_DOG
                            IWDG_Feed();//ι��
#endif
                        }
                    }
#if WATCH_DOG
                    IWDG_Feed();//ι��
#endif
                }
            }
#if WATCH_DOG
            IWDG_Feed();//ι��
#endif
        }
    }
}

uint8_t port_num_config(uint8_t key_word[],uint8_t array[])
{
    uint8_t port_num_key[8][8] = {{0xAF,0x68,0xBE,0x5F,0x4C,0x11,0x57,0x3C},
                                  {0xB4,0xBD,0xFF,0x4F,0x27,0x8C,0x4B,0x23},
                                  {0x96,0x2B,0x57,0xAD,0x04,0xAD,0xC0,0xCA},
                                  {0xDD,0xCD,0xD0,0x67,0x86,0xCB,0x3A,0x52},
                                  {0x4E,0x59,0xA3,0x39,0xB7,0x68,0x46,0xC3},
                                  {0x53,0xB2,0xF5,0x9F,0xCE,0xFF,0x03,0x1E},
                                  {0x8B,0xC2,0xCE,0x77,0x34,0xF0,0xB8,0xB6},
                                  {0xED,0xE4,0xB8,0x52,0x8F,0x05,0x0E,0x56}};
    uint8_t special_key[8][8] = {{0x34,0x00,0xB1,0x11,0x11,0x11,0x11,0x11},
                                 {0x34,0x00,0xB1,0x22,0x22,0x22,0x22,0x22},
                                 {0x34,0x00,0xB1,0x33,0x33,0x33,0x33,0x33},
                                 {0x34,0x00,0xB1,0x44,0x44,0x44,0x44,0x44},
                                 {0x34,0x00,0xB1,0x55,0x55,0x55,0x55,0x55},
                                 {0x34,0x00,0xB1,0x66,0x66,0x66,0x66,0x66},
                                 {0x34,0x00,0xB1,0x77,0x77,0x77,0x77,0x77},
                                 {0x34,0x00,0xB1,0x88,0x88,0x88,0x88,0x88}};
    uint8_t temp[8] = {0};
    uint8_t correct_num = 0;
    
    for(uint8_t i=0;i<8;i++)//����˿����÷���
    {
        for(uint8_t j=0;j<8;j++)
        {
            if(key_word[j+2] == special_key[i][j])
            {
              correct_num++;
              if(correct_num == 8)
              {
                return i+1;
              }
            }
        }
        correct_num = 0;
    }
    
    switch(array[7]%8)
    {
        case 0:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][0];
                  temp[1] = key_word[3] - port_num_key[i][1];
                  temp[2] = key_word[4] - port_num_key[i][2];
                  temp[3] = key_word[5] - port_num_key[i][3];
                  temp[4] = key_word[6] - port_num_key[i][4];
                  temp[5] = key_word[7] - port_num_key[i][5];
                  temp[6] = key_word[8] - port_num_key[i][6];
                  temp[7] = key_word[9] - port_num_key[i][7];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 1:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][1];
                  temp[1] = key_word[3] - port_num_key[i][0];
                  temp[2] = key_word[4] - port_num_key[i][3];
                  temp[3] = key_word[5] - port_num_key[i][2];
                  temp[4] = key_word[6] - port_num_key[i][5];
                  temp[5] = key_word[7] - port_num_key[i][4];
                  temp[6] = key_word[8] - port_num_key[i][7];
                  temp[7] = key_word[9] - port_num_key[i][6];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 2:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][7];
                  temp[1] = key_word[3] - port_num_key[i][6];
                  temp[2] = key_word[4] - port_num_key[i][5];
                  temp[3] = key_word[5] - port_num_key[i][4];
                  temp[4] = key_word[6] - port_num_key[i][3];
                  temp[5] = key_word[7] - port_num_key[i][2];
                  temp[6] = key_word[8] - port_num_key[i][1];
                  temp[7] = key_word[9] - port_num_key[i][0];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 3:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][2];
                  temp[1] = key_word[3] - port_num_key[i][3];
                  temp[2] = key_word[4] - port_num_key[i][0];
                  temp[3] = key_word[5] - port_num_key[i][1];
                  temp[4] = key_word[6] - port_num_key[i][6];
                  temp[5] = key_word[7] - port_num_key[i][7];
                  temp[6] = key_word[8] - port_num_key[i][4];
                  temp[7] = key_word[9] - port_num_key[i][5];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 4:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][3];
                  temp[1] = key_word[3] - port_num_key[i][2];
                  temp[2] = key_word[4] - port_num_key[i][1];
                  temp[3] = key_word[5] - port_num_key[i][0];
                  temp[4] = key_word[6] - port_num_key[i][7];
                  temp[5] = key_word[7] - port_num_key[i][6];
                  temp[6] = key_word[8] - port_num_key[i][5];
                  temp[7] = key_word[9] - port_num_key[i][4];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 5:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][4];
                  temp[1] = key_word[3] - port_num_key[i][5];
                  temp[2] = key_word[4] - port_num_key[i][6];
                  temp[3] = key_word[5] - port_num_key[i][7];
                  temp[4] = key_word[6] - port_num_key[i][0];
                  temp[5] = key_word[7] - port_num_key[i][1];
                  temp[6] = key_word[8] - port_num_key[i][2];
                  temp[7] = key_word[9] - port_num_key[i][3];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 6:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][5];
                  temp[1] = key_word[3] - port_num_key[i][4];
                  temp[2] = key_word[4] - port_num_key[i][7];
                  temp[3] = key_word[5] - port_num_key[i][6];
                  temp[4] = key_word[6] - port_num_key[i][1];
                  temp[5] = key_word[7] - port_num_key[i][0];
                  temp[6] = key_word[8] - port_num_key[i][3];
                  temp[7] = key_word[9] - port_num_key[i][2];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
        case 7:
          {
              for(uint8_t i=0;i<8;i++)
              {
                  temp[0] = key_word[2] - port_num_key[i][6];
                  temp[1] = key_word[3] - port_num_key[i][7];
                  temp[2] = key_word[4] - port_num_key[i][5];
                  temp[3] = key_word[5] - port_num_key[i][4];
                  temp[4] = key_word[6] - port_num_key[i][3];
                  temp[5] = key_word[7] - port_num_key[i][2];
                  temp[6] = key_word[8] - port_num_key[i][0];
                  temp[7] = key_word[9] - port_num_key[i][1];
                  for(uint8_t j=0;j<8;j++)
                  {
                      if(temp[j] == array[j])
                      {
                          correct_num++;
                          if(correct_num == 8)return i+1;
                      }
                  }
              }
          }break;
    }
    return 0;
}
