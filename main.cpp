#include <GL/gl.h>
#include <GL/glut.h>
#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<bits/stdc++.h>
#include<string>

using namespace std;

long long int runtime = 0;//runtime counter of the project
long long int third_frame_time = 0;
int flag = 1;
int run_first_frame=1;
int run_second_frame=0;
int text_in_first_frame=0;
int bowl_start = 0;
int bowl_swing_type = 0;
int bowl_delivered = 0;
int game_over = 0;
int score = 0;
int hit = 0;

int bowl_hit_direction = 0; //hit by batsman
int bowl_hit_direction_temp = 0;

float circle_move = 0.0;
float line_move = 0.0;
float cloud_move = 0.0;
float car1_move = 0.0;
float car2_move = 0.0;
float bird_move = 0.0;
float bird_wing_move = 0.0;
float swing_move = 0.0;
float play_item1 = 0.0;
float play_item2 = 0.0;
float bowler_run = 0.0;
float bowler_leg = 0.0;
float bowling_hand = 0.0;


float bowl_move_y = 0.0;
float bowl_move_x = 0.0;
float bowl_bounce = 0.0;
float bowl_swing = 0.0;
float change_text_color = 0.0;
float bowl_up_down = 0.0;
float bowl_marker_x = 0.0;
float bowl_marker_y = 0.0;
float bowl_swing_range = 0.0;
float bowl_speed = 0.0;


//batsman variable
float batsman_move = 0.0;
float bat_move = 0.0;
float dis_bet_bat_bowl = 0.0;






//function prototype
void timer(int);
void create_reactanlge(float x1,float y1, float x2,float y2,float x3,float y3,float x4,float y4);
void create_triangle(float x1,float y1, float x2,float y2,float x3,float y3);
void create_cirle(float x,float y,float radius,float circle_move);
void create_line(float x1,float y1,float x2,float y2);
void text(float x, float y, int font_type, string s);
void bowlcontrol(unsigned char key,int x, int y);
float distance(float x1, float y1, float x2, float y2);
void third_frame_helper();
void display(void);
int random(int min_num, int max_num);








//frames
void first_frame()
{
    glColor3ub(145, 134, 131);
    create_reactanlge(0,0,100,0,100,100,0,100);

    //ground outer circle
    glColor3ub(36, 71, 46);
    create_cirle(50,50,40,circle_move);

    //ground inner circle
    glColor3ub(16, 143, 18);
    create_cirle(50,50,23,circle_move);

    //pitch
    glColor3ub(242, 228, 211);
    create_reactanlge(45-circle_move,38-circle_move,55+circle_move,38-circle_move,55,65,45,65);
    glColor3ub(0,0,0);
    create_line(45-line_move,41-line_move,55+line_move,41-line_move);
    create_line(45,62,55,62);

    if(text_in_first_frame){
        string message = "Welcome To Cricket World";
        string created_by = "Created By - R.A.S Team";
        string sharif = "Md Sharif Khan         181-15-2002";
        string anika = "Anika Alam              181-15-1926";
        string rumman = "Rumman Ahmed          181-15-1800";
        glColor3ub(204, 14, 14);
        text(40,59,1,message);
        text(40,56,2,created_by);
        text(40,53,1,sharif);
        text(40,50,1,anika);
        text(40,47,1,rumman);
        //bowl
        glColor3ub(255,0,0);
        create_cirle(54,43+bowl_up_down,2,0);
        //stamps
        glColor3ub(0,0,0);
        create_reactanlge(45+2,29,46.5+2,29,46.5+2,40,45+2,40);
        create_reactanlge(47+2,29,48.5+2,29,48.5+2,40,47+2,40);
        create_reactanlge(49+2,29,50.5+2,29,50.5+2,40,49+2,40);
    }
}


void sun()
{
    //sun
    glColor3ub(237, 181, 28);
    create_cirle(90,90,7,0);
}

void cloud(float x,float y,float r)
{
    //cloud
    glColor3ub(227, 221, 207);
    create_cirle(x+cloud_move,y,r,0);
    create_cirle(x+2+cloud_move,y+4,r,0);
    create_cirle(x+4+cloud_move,y,r,0);
}

void car(float bwx,float fwx,float wy,float wr,float mfx,float mfy,float speed,float mr,float mb,float mg,float sr,float sb,float sg)
{
    glColor3ub(0,0,0);
    create_cirle(bwx+speed,wy,wr,0);
    create_cirle(fwx+speed,wy,wr,0);
    glColor3ub(sr,sb,sg);
    create_reactanlge(mfx+4+speed,mfy,mfx+14+speed,mfy,mfx+11+speed,mfy+4,mfx+7+speed,mfy+4);
    glColor3ub(mr,mb,mg);
    create_reactanlge(mfx+speed,wy,mfx+20+speed,wy,mfx+20+speed,mfy,mfx+speed,mfy);
}

void house(float br,float bb, float bg,float tr,float tb,float tg,float bx1,float by1,float bx2,float by2)
{
    glColor3ub(br, bb, bg);
    create_reactanlge(bx1,by1,bx2,by1,bx2,by2,bx1,by2);
    glColor3ub(tr,tb,tg);
    create_triangle(bx1-2,by2,bx2+2,by2,(bx1+bx2)/2,by2+3);
}

void person(float x,float y)
{
    glColor3ub(0,0,0);
    create_cirle(x,y,1.25,0);
    create_line(x,y,x,y-3);
    create_reactanlge(x-1,y-5,x+1,y-5,x+1,y-2,x-1,y-2);
    create_line(x-.25,y-5,x-.25,y-7);
    create_line(x+.5,y-5,x+.5,y-7);
}


void bird(float x,float y,float bm,float bw)
{
    create_line(x-bm,y-bw,x+2-bm,y);
    create_line(x+2-bm,y,x+3-bm,y-2);
    create_line(x+3-bm,y-2,x+4-bm,y);
    create_line(x+4-bm,y,x+6-bm,y-bw);

}

void second_frame()
{
    glColor3ub(178, 201, 237); //sky
    create_reactanlge(0,70,100,70,100,100,0,100);
    glColor3ub(72, 189, 70); // ground
    create_reactanlge(0,0,100,0,100,70,0,70);

    //road
    glColor3ub(154, 161, 151);
    create_reactanlge(0,25,100,25,100,41,0,41);
    glColor3ub(255,255,255); //divider
    create_reactanlge(0,32.5,100,32.5,100,33.5,0,33.5);

    //road in playground
    glColor3ub(154, 161, 151);
    create_reactanlge(40,41,44,41,44,70,40,70);

    //car
    car(10,20,38,2,5,42.5,car1_move,89, 56, 72,36, 110, 50);
    car(30,40,28,2,25,32.5,car2_move,11, 123, 72,36, 110, 134);


//    glColor3ub(0,0,0);
//    create_cirle(32+cycle_move,35.5,2.5,0);
//    create_cirle(42+cycle_move,35.5,2.5,0);
//    glColor3ub(47, 55, 105);
//    create_cirle(35+cycle_move,39,5,0);
//    glColor3ub(64, 13, 6);
//    create_reactanlge(27+cycle_move,35.5,45+cycle_move,35.5,45+cycle_move,40,27+cycle_move,40);

//    bowler
//    glColor3ub(255,255,255);
//    create_cirle(50,20,3.8,0);
//    glColor3ub(0,0,0);
//    create_cirle(48.5,21,0.6,0);
//    create_cirle(51.5,21,0.6,0);



//    create_line(10+cycle_move,37.95,20+cycle_move,37.95);
//    create_line(10+cycle_move,37.95,15+cycle_move,35.5);
//    create_line(15+cycle_move,35.5,20+cycle_move,37.95);
//    create_cirle(15+cycle_move,35.5,0.8,0);
//    create_line(10+cycle_move,35.5,15+cycle_move,35.5);
//    create_line(10+cycle_move,37.95,10+cycle_move,35.5);


    //sun
    sun();

    //cloud
    cloud(9,80,4);
    cloud(5,90,3);
    cloud(18,83,3);

    //birds
    glColor3ub(0,0,0);
    bird(70,90,bird_move,bird_wing_move);
    bird(64,88,bird_move,bird_wing_move);
    bird(76,88,bird_move,bird_wing_move);
//    bird(82,90,bird_move,bird_wing_move);


    //swing
    glColor3ub(102,0,51);
    int left = 18;
    create_reactanlge(70+left,49,70.5+left,49,70.5+left,59,70+left,59);
    create_reactanlge(80+left,49,80.5+left,49,80.5+left,59,80+left,59);
    create_line(69+left,59,81.5+left,59);
    create_line(73+left,59,73+left,51.5-swing_move);
    create_line(77+left,59,77+left,51.5-swing_move);
    create_reactanlge(73+left,51.5-swing_move,77+left,51.5-swing_move,77+left,52-swing_move,73+left,52-swing_move);

    //
    create_reactanlge(60+left,52,61+left,52,61+left,55,60+left,55);
    create_reactanlge(54+left,55-play_item1,67+left,55-play_item2,67+left,55.5-play_item2,54+left,55.5-play_item1);


    //building
//    house(214, 134, 105,0,0,0,30,55,37,60);
    house(214, 134, 105,0,0,0,3,58,8,63);


    glColor3ub( 153,0,76);
    create_reactanlge(25,48,38,48,38,66,25,66);
    glColor3ub(255,255,51);
    create_reactanlge(25,66,38,66,38,69,25,69);

    glBegin(GL_TRIANGLES);
    glVertex3i(23,66,0);
    glVertex3i(25,69,0);
    glVertex3i(25,66,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3i(38,66,0);
    glVertex3i(40,66,0);
    glVertex3i(38,69,0);
    glEnd();
//2nD building
     glColor3ub(0,0,102);
    create_reactanlge(46,48,58,48,58,66,46,66);
    glColor3ub(255,255,51);
    create_reactanlge(46,65,58,65,58,68,46,68);
    glBegin(GL_TRIANGLES);
    glVertex3i(44,65,0);
    glVertex3i(46,65,0);
    glVertex3i(46,68,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3i(58,65,0);
    glVertex3i(60,65,0);
    glVertex3i(58,68,0);
    glEnd();
    //2nD building window

     glColor3ub(255,255,51);
    create_reactanlge(47,50,50,50,50,55,47,55);
     glColor3ub(255,255,51);
    create_reactanlge(47,58,50,58,50,63,47,63);
     glColor3ub(255,255,51);
    create_reactanlge(53,50,56,50,56,55,53,55);
     glColor3ub(255,255,51);
    create_reactanlge(53,58,56,58,56,63,53,63);


    //1st building window
    glColor3ub(255,255,51);
    create_reactanlge(27,50,30,50,30,55,27,55);
    glColor3ub( 255,255,51);
    create_reactanlge(33,50,36,50,36,55,33,55);
     glColor3ub( 255,255,51);
    create_reactanlge(27,58,30,58,30,63,27,63);
     glColor3ub( 255,255,51);
    create_reactanlge(33,58,36,58,36,63,33,63);

    //persons
//    person(20,10);
//    person(70,60);

    //cricket pitch
    glColor3ub(242, 228, 211);
    create_reactanlge(30,10,60,10,60,15,30,15);
    glColor3ub(0,21,0);
    create_line(33,10,33,15);
    create_line(57,10,57,15);

    //trees
    //1st tree base
    glColor3ub(153,76,0);
    create_reactanlge(10,45,12,45,12,55,10,55);
    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(10,45,0);
    glVertex3i(8,47,0);
    glVertex3i(11,45,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(11,45,0);
    glVertex3i(12,45,0);
    glVertex3i(14,50,0);
    glEnd();

    //1st tree leaves
    glColor3ub(20, 110, 45);
    create_cirle(10,55,4,0);
    create_cirle(11,56,4,0);
    create_cirle(11,58,4,0);
    create_cirle(12,55,4,0);

    //2nd tree base
    glColor3ub(153,76,0);
    create_reactanlge(18,49,20,49,20,56,18,56);

    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(18,49,0);
    glVertex3i(19,49,0);
    glVertex3i(17,52,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(19,49,0);
    glVertex3i(20,49,0);
    glVertex3i(22,51,0);
    glEnd();

    //2nd tree leaves
    glColor3ub(20, 110, 45);
    create_cirle(18,57,4,0);
    create_cirle(19,58,4,0);
//    create_cirle(19,60,4,0);
//    create_cirle(18,57,4,0);

    //3rd tree base
    glColor3ub(153,76,0);
    create_reactanlge(3,42,5,42,5,49,3,49);

    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(3,42,0);
    glVertex3i(4,42,0);
    glVertex3i(2,44,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(153,255,51);
    glVertex3i(4,42,0);
    glVertex3i(5,42,0);
    glVertex3i(6,44,0);
    glEnd();

    //3rd tree leaves
    glColor3ub(20, 110, 45);
    create_cirle(3,49,2.5,0);
    create_cirle(4,50,2.5,0);
    create_cirle(4,48,2.5,0);
    create_cirle(5,49,2.5,0);

}

void stumps(float x1,float y1,float x2,float y2)
{
    create_reactanlge(x1,y1,x2,y1,x2,y2,x1,y2);
    create_reactanlge(x1+1,y1,x2+1,y1,x2+1,y2,x1+1,y2);
    create_reactanlge(x1+2,y1,x2+2,y1,x2+2,y2,x1+2,y2);

}

void bowler()
{
    glPushMatrix();
    glTranslatef(0,bowler_run,0);
    glColor3ub(99, 85, 67);
    glBegin(GL_POLYGON);//leg
    glVertex3f(40,23,0);
    glVertex3f(40,10-bowler_leg,0);
    glVertex3f(40.5,10-bowler_leg,0);
    glVertex3f(42,23,0);
    glVertex3f(42.5,10+bowler_leg,0);
    glVertex3f(43,10+bowler_leg,0);
    glVertex3f(43,23,0);
    glEnd();
    glColor3ub(204, 150, 22);
    //body
    create_reactanlge(40,20,43,20,43,27,40,27);
    //left hand
    create_reactanlge(38.5,21.5+bowler_leg+bowling_hand,39,21.5+bowler_leg+bowling_hand,40,27,39,27);
    //right hand
    create_reactanlge(44,21.5-bowler_leg,44.5,21.5-bowler_leg,44,27,43,27);
    glColor3ub(237, 231, 204);
    //neck
    create_reactanlge(41,29.5,42,29.5,42,27,41,27);
    //head
    glColor3ub(0,0,0);
    create_cirle(41.5,30,1.4,0);
    glPopMatrix();

}

void bat_direction()
{
    if(bowl_hit_direction_temp==1){
        create_reactanlge(49+batsman_move+bat_move,56,49.5+batsman_move+bat_move,56,49.5+batsman_move+bat_move,57.24,49+batsman_move+bat_move,57.24);
        create_reactanlge(48.75+batsman_move-2,51,49.75+batsman_move-2,51,49.75+batsman_move,56,48.75+batsman_move,56);
    }
    else{
        create_reactanlge(49+batsman_move+bat_move,56,49.5+batsman_move+bat_move,56,49.5+batsman_move+bat_move,57.24,49+batsman_move+bat_move,57.24);
        create_reactanlge(48.75+batsman_move,51,49.75+batsman_move,51,49.75+batsman_move,56,48.75+batsman_move,56);//bat
    }

}

void batsman()
{
    glColor3ub(255,0,0);
    create_reactanlge(50+batsman_move,51,51+batsman_move,51,51+batsman_move,56,50+batsman_move,56);//legs
    create_reactanlge(50+batsman_move,56,53+batsman_move,57,53+batsman_move,59,50+batsman_move,57);//lower body
    create_reactanlge(52+batsman_move,57,53+batsman_move,57,52+batsman_move,65,51+batsman_move,64);//body
    create_reactanlge(49+batsman_move+bat_move,57,49.8+batsman_move+bat_move,57,52+batsman_move,62,52+batsman_move,62.25);//arms
    glColor3ub(255,255,255);
    create_reactanlge(49+batsman_move+bat_move,56,49.5+batsman_move+bat_move,56,49.5+batsman_move+bat_move,57.24,49+batsman_move+bat_move,57.24);//bat handle
//    bat_direction(); //added
    create_reactanlge(48.75+batsman_move+bat_move,51,49.75+batsman_move+bat_move,51,49.75+batsman_move+bat_move,56,48.75+batsman_move+bat_move,56);//bat
    glColor3ub(209, 206, 199);
    create_cirle(51+batsman_move,65,1.4,0);//head

}

void reset()
{
     batsman_move = 0.0;
     bat_move = 0.0;
     dis_bet_bat_bowl = 0.0;
     bowl_marker_x = 0.0;
     bowl_marker_y = 0.0;
     bowl_swing_range = 0.0;
     bowl_speed = 0.0;
     bowl_move_y = 0.0;
     bowl_move_x = 0.0;
     bowl_bounce = 0.0;
     bowl_swing = 0.0;
     bowler_run = 0.0;
     bowler_leg = 0.0;
     bowling_hand = 0.0;
     hit = 0;
     bowl_hit_direction = 0;
     bowl_hit_direction_temp = 0;
     bowl_start = 0;
     bowl_swing_type = 0;
     bowl_delivered = 0;
     third_frame_time = 0;

}



void third_frame()
{
    glColor3ub(47, 158, 86);
    create_reactanlge(0,0,100,0,100,100,0,100);

    //pitch
    float a = 13;
    glColor3ub(165, 171, 111);
    create_reactanlge(44-a,47-a,54+a,47-a,56,54,42,54);
    glColor3ub(255,255,255);
    create_line(35,40,63,40); //bowler side
    create_line(41,51.5,57,51.5);


    if(bowl_start==0){
        //bowl_marker
        glColor3ub(244,122,234);
        create_cirle(45+bowl_marker_x,47+bowl_marker_y,0.85,0);
    }
    glColor3ub(0,0,0);
    stumps(48,54,48.5,61);
    stumps(49,35,49.55,45); //bowler side


    glColor3ub(255,0,0);
    if(bowl_start==0){
        string start_message = "Press space to bowl";
        text(39,4,4,start_message);
    }

    string bm1 = "Press < to move left";
    text(80,90,1,bm1);
    string bm2 = "Press > to move left";
    text(80,85,1,bm2);
    string bm3 = "Press K for hit offside";
    string bm4 = "Press L for defense";
    string bm5 = "Press ; for hit legside";
    text(80,80,1,bm3);
    text(80,75,1,bm4);
    text(80,70,1,bm5);

    if(bowl_swing_type == 0){
        string in_swing = "Press I For inswing";
        string out_swing = "Press O For outswing";
        text(3,8,1,in_swing);
        text(3,3,1,out_swing);
    }

    if(bowl_speed==0.0 && bowl_swing_type !=0){
        string fast = "Press F for faster bowl";
        string slow = "Press G for slower bowl";
        text(3,8,1,fast);
        text(3,3,1,slow);
    }
    glColor3ub(255,0,0);
    if(bowl_speed!=0.0 && bowl_swing_range==0.0 && bowl_swing_type !=0){
        string low = "Press T for low swing";
        string mid = "Press Y for Medium swing";
        string high = "Press U for High swing";
        text(2,9,1,low);
        text(2,5,1,mid);
        text(2,1,1,high);
    }
    if(game_over){
        string out_message= "Bowled!!!";
        string m1 = "Game Over";
        text(40,70,1,out_message);
        text(40,75,1,m1);
    }
//    printf("%d \n",score);
    stringstream ss;
    ss<<score;
    string score_str = ss.str();
    string score_mes = "Score: ";
    text(5,90,1,score_mes);
    text(10,90,1,score_str);
    //bowl
    if(bowl_delivered){
        glColor3ub(255,0,0);
        if(bowl_bounce<15 && bowl_hit_direction==0 &&game_over==0)
        {
            float dis = distance(39+bowl_move_x+bowl_swing,63.5+bowl_move_y+bowl_bounce,48.5,56);
            if(dis<1.5)
            {
                game_over = 1;
                printf("Game over");
            }

//            printf("Bowl %f %f\n",39+bowl_move_x+bowl_swing,63.5+bowl_move_y+bowl_bounce);
            create_cirle(39+bowl_move_x+bowl_swing,63.5+bowl_move_y+bowl_bounce,0.85,0);

            dis_bet_bat_bowl = distance(49.25+batsman_move+bat_move,55,39+bowl_move_x+bowl_swing,63.5+bowl_move_y+bowl_bounce);
            if(dis_bet_bat_bowl<1.5)
                {
                    bowl_hit_direction = bowl_hit_direction_temp;
                    printf("Connected\n");
                    cout<<dis_bet_bat_bowl<<" "<<endl;
                    hit = 1;
                }

        }else if(bowl_bounce<18 && game_over ==0){
            create_cirle(39+bowl_move_x+bowl_swing,63.5+bowl_move_y+bowl_bounce,0.85,0);
            third_frame_time++;
//            cout<<"third "<<third_frame_time<<endl;
            if(third_frame_time > 200 ||bowl_bounce >=17.5)
            {
                cout<<"reset"<<endl;
                reset();
            }
        }

    }

    bowler();
    batsman();

}




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(run_first_frame)
        first_frame();
    else if(run_second_frame)
        second_frame();
    else
        third_frame();

    glutSwapBuffers();
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -10.0, 10.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  //add GLUT_DOUBLE
    glutInitWindowSize(1200,680);
    glutInitWindowPosition (50, 10);
    glutCreateWindow ("Cricket Match");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(bowlcontrol);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
    return 0;
}


void first_frame_helper()
{
    if(runtime%40==1){
        if(flag){
            flag = 0;
            bowl_up_down += 3;
        }else{
            flag = 1;
            bowl_up_down -= 3;
        }
    }
    if(runtime>700&&runtime<1100)
    {
        text_in_first_frame = 1 ;
        //change_text_color += 0.7;
    }
    if(runtime>300 && runtime<700)
    {
        circle_move += 0.04;
        line_move += 0.03;
    }

}

//circle
// reactangle
// triangle
// line


void second_frame_helper(){
    run_second_frame = 1;
    run_first_frame = 0;
    cloud_move += 0.025;
    car1_move += 0.07;
    car2_move += 0.04;
    bird_move += 0.05;

    if(runtime%50==1){
        if(flag==1){
            flag = 0;
        }else{
            flag = 1;
        }
    }
    if(flag){
        bird_wing_move = 1;
        swing_move += 0.02;
        play_item1 = 0.85;
        play_item2 = -0.85;
    }
    else{
        bird_wing_move = -1;
        swing_move -= 0.02;
        play_item1 = -0.85;
        play_item2 = 0.85;
    }
}

void third_frame_helper()
{
//    printf("%f\n",bowler_run);
    run_first_frame = 0;
    run_second_frame = 0;
    if(bowl_start){
        if(bowler_run<25)
        {
            bowler_run += 0.15;
            if(runtime%40==0){
             if(flag==0){
                bowler_leg=1;
                flag=1;
             }else{
               bowler_leg=-1;
               flag=0;
             }
            }
        }else{
            bowling_hand = 10;
            bowl_delivered = 1;
        }
    }
//    printf("Bowl %f %f\n",39+bowl_move_x,63.5+bowl_move_y);
//    printf("marker %f %f\n",45+bowl_marker_x,47+bowl_marker_y);

    if(bowl_delivered&&bowl_hit_direction==0)
        {
            bowling_hand -= 0.1;
            if(bowl_swing_type==1){
                if(floor(45+bowl_marker_x) != floor(39+bowl_move_x))
                {
                    bowl_move_x += 0.25;
                }else{
                    bowl_swing += bowl_swing_range;
                }
                if(floor(47+bowl_marker_y)!=floor(63.5+bowl_move_y)){
                    bowl_move_y -= bowl_speed;
                }
                else{
                    bowl_bounce += bowl_speed;
                }
            }else{
                if(floor(45+bowl_marker_x) != floor(39+bowl_move_x))
                {
                    bowl_move_x += 0.25;
                }else{
                    bowl_swing -= bowl_swing_range;
                }
                if(floor(47+bowl_marker_y)!=floor(63.5+bowl_move_y)){
                    bowl_move_y -= bowl_speed;
                }
                else{
                    bowl_bounce += bowl_speed;
                }
            }
        }else if(bowl_delivered&&bowl_hit_direction==1){
            {
                if(dis_bet_bat_bowl>=1.0 && dis_bet_bat_bowl <= 1.12)
                    {
                        bowl_move_x -= 0.6;
                        bowl_move_y += 0.7;
                        if(hit)
                            {
                                score += random(4,6);
                                hit = 0;
                            }
                    }
                else if(dis_bet_bat_bowl>=1.13 && dis_bet_bat_bowl<=1.22){
                    bowl_move_x -= 0.3;
                    bowl_move_y += 0.4;
                    if(hit)
                        {
                            score += random(3,4);
                            hit = 0;
                        }
                }
                else if(dis_bet_bat_bowl>=1.23 && dis_bet_bat_bowl<=1.3){
                    bowl_move_x -= 0.5;
                    bowl_move_y -= 0.4;
                    if(hit)
                        {
                            score += random(2,3);
                            hit = 0;
                        }

                }else{
                    bowl_move_x -= 0.1;
                    bowl_move_y -= 0.2;
                    if(hit)
                        {
                            score += random(0,3);
                            hit = 0;
                        }
                }
            }
        }else if(bowl_delivered && bowl_hit_direction==-1){
            {
                bowl_move_y -= 0.02;
            }
        }else if(bowl_delivered&&bowl_hit_direction==2){
            if(dis_bet_bat_bowl>=1.0 && dis_bet_bat_bowl <= 1.12)
                    {
                        bowl_move_x += 0.6;
                        bowl_move_y += 0.7;
                        if(hit)
                        {
                            score += random(4,6);
                            hit = 0;
                        }
                    }
                else if(dis_bet_bat_bowl>=1.13 && dis_bet_bat_bowl<=1.22){
                    bowl_move_x += 0.3;
                    bowl_move_y += 0.4;
                    if(hit)
                        {
                            score += random(3,4);
                            hit = 0;
                        }
                }
                else if(dis_bet_bat_bowl>=1.23 && dis_bet_bat_bowl<=1.3){
                    bowl_move_x += 0.5;
                    bowl_move_y -= 0.4;
                    if(hit)
                        {
                            score += random(2,3);
                            hit = 0;
                        }

                }else{
                    bowl_move_x += 0.1;
                    bowl_move_y -= 0.2;
                    if(hit)
                        {
                            score += random(0,3);
                            hit = 0;
                        }
                }
        }

}



void timer(int){
    runtime++;
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    //printf("Runtime %d\n",runtime);
    if(runtime>=0 && runtime <= 1200)
        first_frame_helper();
    else if(runtime>1200 && runtime <=2400)
        second_frame_helper();
    else
        third_frame_helper();


}


//reactangle function
void create_reactanlge(float x1,float y1, float x2,float y2,float x3,float y3,float x4,float y4)
{
    glBegin(GL_QUADS);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x3,y3,0);
    glVertex3f(x4,y4,0);
    glEnd();
}
//trinagle function
void create_triangle(float x1,float y1, float x2,float y2,float x3,float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glVertex3f(x3,y3,0);
    glEnd();
}

void create_cirle(float x,float y,float radius,float cm)
{
    glBegin(GL_POLYGON);
    float ang=0;
    for(int i=0;i<360;i++){
        ang = i*3.142/180;
        glVertex2f(x+(radius+cm)*cos(ang),y+(radius+cm)*sin(ang));
    }
    glEnd();
}


void create_line(float x1,float y1,float x2,float y2)
{
    glBegin(GL_LINES);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2,0);
    glEnd();
}

void text(float x, float y, int font_type, string text)
{
    glRasterPos2f(x, y);
    int len, i;
    len = text.length();
    for (i = 0; i < len; i++)
    {
        switch(font_type){
            case 1:
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
                break;
            case 2:
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
                break;
            default:
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
                break;
        }
    }
}




//void bowl_control

void bowlcontrol(unsigned char key,int x, int y)
{
    printf(" %d\n",key);
    switch(key){
    case 32:
        if(bowl_swing_type==1 || bowl_swing_type== 2)
            bowl_start = 1;
        break;
    case 105:
        bowl_swing_type = 1;
        break;
    case 111:
        bowl_swing_type = 2;
        break;
    case 97:
        if(bowl_marker_x>-3)
            bowl_marker_x -= 1;
        break;
    case 119:
        if(bowl_marker_y<6)
            bowl_marker_y += 1;
        break;
    case 115:
        if(bowl_marker_y>-4)
            bowl_marker_y -= 1;
        break;
    case 100:
        if(bowl_marker_x<5)
            bowl_marker_x += 1;
        break;
    case 116:
        if(bowl_swing_type == 1 || bowl_swing_type == 2)
            bowl_swing_range += 0.05;
        break;
    case 121:
        if(bowl_swing_type == 1 || bowl_swing_type == 2)
            bowl_swing_range += 0.08;
        break;
    case 117:
        if(bowl_swing_type == 1 || bowl_swing_type == 2)
            bowl_swing_range += 0.12;
        break;
    case 102:
        if(bowl_swing_type == 1 || bowl_swing_type == 2)
            bowl_speed = 0.4;
        break;
    case 103:
        if(bowl_swing_type == 1 || bowl_swing_type == 2)
            bowl_speed = 0.2;
        break;

    case 44:
        if(batsman_move>-5)
            batsman_move -= 0.6;
        break;
    case 46:
        if(batsman_move<5)
            batsman_move += 0.6;
        break;
    case 107:
        if(bowl_delivered){
            bowl_hit_direction_temp = 1;
            bat_move = -1.5;
        }
        break;
    case 108:
        if(bowl_delivered){
            bat_move = 0;
            bowl_hit_direction_temp = -1;
        }
        break;
    case 59:
        if(bowl_delivered){
            bowl_hit_direction_temp = 2;
            bat_move = 1.5;
        }
        break;
//    glutPostRedisplay();
    }
}

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2));
}


int random(int min_num, int max_num)
{
    return (rand()%(max_num-min_num))+min_num;
}


