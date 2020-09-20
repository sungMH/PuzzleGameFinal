/*
* 게임명: 퍼즐게임
* 작성자: 중앙대학교 수학과 20153797 성명현
* 작성일: 2020-09-18~2020-09-20
* 업데이트 현황: version1.0 : 한 개의 퍼즐에 관한 게임
*					-추후 버젼을 2.0으로 업데이트 하기 위한 준비 코드 주석처리
*					-2.0 버젼에서는 3개의 퍼즐 모양 제공
*/


#include <bangtal.h>
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace bangtal;

typedef struct puzzlnfo {
	ObjectPtr op;//퍼즐 조각
	//다음은 퍼즐의 고유 번호- 원래 적절한 위치를 기억- 공백은 4,4를 기억한다.
	//게임중 바뀌면 안된다.
	int x;//원래 위치의 x좌표
	int y;//원래 위치의 y좌표
}puzzleinfo;

//4*4퍼즐 조각의 위치를 저장할 장소
int puzzlePoint[4][4][2] = {
	{{397,449},{523,449},{649,449},{775,449}},
	{{397,323},{523,323},{649,323},{775,323}},
	{{397,197},{523,197},{649,197},{775,197}},
	{{397,74},{523,74},{649,74},{775,74}}
};

//배경화면 선언
ScenePtr backgroundScene[3];

//타이타닉, 티모, 정도전 파일 저장위치
char fileName1[16][45] = {//추후 버젼 업그레이드 하면서 구현

};
char fileName2[16][45] = {
	"images2/부분-001.png",
	"images2/부분-002.png",
	"images2/부분-003.png",
	"images2/부분-004.png",
	"images2/부분-005.png",
	"images2/부분-006.png",
	"images2/부분-007.png",
	"images2/부분-008.png",
	"images2/부분-009.png",
	"images2/부분-010.png",
	"images2/부분-011.png",
	"images2/부분-012.png",
	"images2/부분-013.png",
	"images2/부분-014.png",
	"images2/부분-015.png",
	"images2/공백.png"
};
char fileName3[16][45] = {//추후 버젼 업그레이드 하면서 구현

};

puzzleinfo pz[4][4];
ObjectPtr fracOfPuzz[4][4];//퍼즐 조각 객체 배열- 원본
ObjectPtr fracOfPuzz1[4][4];//퍼즐 조각 객체 배열- 섞은다음

//티모 퍼즐 조각 붙이기

//i번 째 퍼즐에 대한 정보를 받아 퍼즐을 무작위로 섞어주고 
//섞인 퍼즐에 대해서 마우스콜백을 부착하여
//마우스가 움직일 때 마다 모든 퍼즐의 위치가 옳은 위치인지
//파악하여 모든 조각이 올바른 위치이면 게임을 끝낸다.
//마우스를 클릭할때 주변에 빈 칸이 있으면 빈칸으로 움직이도록 설정한다.
//공백은 마지막 칸이 되도록 설정한다.
//여기서는 4*4로 통일

void startGame1(ScenePtr scene, int i) {

	scene->enter();
	srand((unsigned int)time(0));

	//퍼즐의 위치를 숫자로 나타낸 배열
	int wherePuzzle[4][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};

	//4*4공간을 1~16순서로 숫자매긴다음 랜덤으로 배치된 곳은 1로 처리해서 
	//같은 곳에 퍼즐 조각 배치되지 못하도록 방지
	int pullEmpty[4][4];
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			pullEmpty[j][k] = 0;
		}
	}



	//퍼즐 생성하는 과정
	if (i == 0) {//타이타닉//추후 버젼 업그레이드 하면서 구현

	}
	else if (i == 1) {//티모
		int l = 0;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				fracOfPuzz[j][k] = Object::create(fileName2[l++], scene, puzzlePoint[j][k][0], puzzlePoint[j][k][1]);
				pz[j][k].op = fracOfPuzz[j][k];
				pz[j][k].x = j;
				pz[j][k].y = k;
				fracOfPuzz[j][k]->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
					int a, b;
					for (int m = 0; m < 4; m++) {
						for (int n = 0; n < 4; n++) {
							if (pz[m][n].op == o) {
								a = m, b = n;
							}
						}
					}

					std::cout << pz[a][b].x << pz[a][b].y << std::endl;
					std::cout << a << b << std::endl;

					if (a - 1 >= 0) {//상
						if (pz[a - 1][b].x == 3 && pz[a - 1][b].y == 3) {
							pz[a][b].op->locate(backgroundScene[1], puzzlePoint[a - 1][b][0], puzzlePoint[a - 1][b][1]);
							pz[a - 1][b].op->locate(backgroundScene[1], puzzlePoint[a][b][0], puzzlePoint[a][b][1]);
							pz[a][b].op->show();
							pz[a - 1][b].op->show();
							ObjectPtr temp = pz[a - 1][b].op;
							pz[a - 1][b].op = pz[a][b].op;
							pz[a][b].op = temp;
							int temx = pz[a - 1][b].x, temy = pz[a - 1][b].y;
							pz[a - 1][b].x = pz[a][b].x, pz[a - 1][b].y = pz[a][b].y;
							pz[a][b].x = temx, pz[a][b].y = temy;
							return true;
						}
					}

					if (b - 1 >= 0) {//좌
						if (pz[a][b - 1].x == 3 && pz[a][b - 1].y == 3) {
							pz[a][b].op->locate(backgroundScene[1], puzzlePoint[a][b - 1][0], puzzlePoint[a][b - 1][1]);
							pz[a][b - 1].op->locate(backgroundScene[1], puzzlePoint[a][b][0], puzzlePoint[a][b][1]);
							pz[a][b].op->show();
							pz[a][b - 1].op->show();
							ObjectPtr temp = pz[a][b - 1].op;
							pz[a][b - 1].op = pz[a][b].op;
							pz[a][b].op = temp;
							int temx = pz[a][b - 1].x, temy = pz[a][b - 1].y;
							pz[a][b - 1].x = pz[a][b].x, pz[a][b - 1].y = pz[a][b].y;
							pz[a][b].x = temx, pz[a][b].y = temy;
							return true;
						}
					}

					if (a + 1 <= 3) {//하
						if (pz[a + 1][b].x == 3 && pz[a + 1][b].y == 3) {
							pz[a][b].op->locate(backgroundScene[1], puzzlePoint[a + 1][b][0], puzzlePoint[a + 1][b][1]);
							pz[a + 1][b].op->locate(backgroundScene[1], puzzlePoint[a][b][0], puzzlePoint[a][b][1]);
							//pz[a][b].op->show();
							//pz[a+1][b].op->show();
							ObjectPtr temp = pz[a + 1][b].op;
							pz[a + 1][b].op = pz[a][b].op;
							pz[a][b].op = temp;
							int temx = pz[a + 1][b].x, temy = pz[a + 1][b].y;
							pz[a + 1][b].x = pz[a][b].x, pz[a + 1][b].y = pz[a][b].y;
							pz[a][b].x = temx, pz[a][b].y = temy;
							return true;
						}
					}

					if (b + 1 <= 3) {//우
						if (pz[a][b + 1].x == 3 && pz[a][b + 1].y == 3) {
							pz[a][b].op->locate(backgroundScene[1], puzzlePoint[a][b + 1][0], puzzlePoint[a][b + 1][1]);
							pz[a][b + 1].op->locate(backgroundScene[1], puzzlePoint[a][b][0], puzzlePoint[a][b][1]);
							pz[a][b].op->show();
							pz[a][b + 1].op->show();
							ObjectPtr temp = pz[a][b + 1].op;
							pz[a][b + 1].op = pz[a][b].op;
							pz[a][b].op = temp;
							int temx = pz[a][b + 1].x, temy = pz[a][b + 1].y;
							pz[a][b + 1].x = pz[a][b].x, pz[a][b + 1].y = pz[a][b].y;
							pz[a][b].x = temx, pz[a][b].y = temy;
							return true;
						}
					}

					//주변에 빈칸이 없으므로 패스

					//여기서 부터는 모든 조각이 제위치에 있는지 검사

					int correct = 0;//퍼즐 조각이 정확한 위치에 있을때마다 1씩 증가
					for (int m = 0; m < 4; m++) {
						for (int n = 0; n < 4; n++) {
							if (pz[m][n].x == m && pz[m][n].y == n) {
								correct++;
							}
						}
					}

					if (correct == 16) {//퍼즐 조각이 모두 맞다면 게임끝
						showMessage("퍼즐 조각을 모두 맞추셨습니다!! GameOver!");
						Sleep(2000);
						endGame();


					}
					return true;
					});

			}
		}
	}
	else {//정도전//추후 버젼 업그레이드 하면서 구현
	}
	//섞는 부분
	int l = 0;

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {

			int x = rand() % 4;
			int y = rand() % 4;
			if (pullEmpty[x][y] != 0) {//이미 채워진 퍼즐
				k--;
				continue;//다시랜덤 숫자 뽑기
			}
			pullEmpty[x][y] = 1;//채워진거 표시


			fracOfPuzz1[x][y] = fracOfPuzz[j][k];
			pz[x][y].op = fracOfPuzz1[j][k];
			pz[x][y].x = j;
			pz[x][y].y = k;
		}
	}

	auto startButton = Object::create("images/start.png", scene, 300, 330);
	//퍼즐게임 시작!
	startButton->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		o->hide();
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				fracOfPuzz[j][k]->hide();
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				fracOfPuzz1[j][k]->locate(backgroundScene[1], puzzlePoint[j][k][0], puzzlePoint[j][k][1]);
				pz[j][k].op = fracOfPuzz1[j][k];
				fracOfPuzz1[j][k]->show();
			}
		}
		return true;
		});

	//여기까지 결과 : 제대로 배치된 퍼즐조각, 그리고 섞인 퍼즐 조각 배열
}




int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);


	//시작화면 생성
	auto scene = Scene::create("게임시작!", "images/게임시작화면.png");
	ScenePtr scenes[3];//난이도 3단계 상 중 하
	scenes[0] = Scene::create("타이타닉3*3", "images1/타이타닉원본.png");
	scenes[1] = Scene::create("티모4*4", "images2/티모.png");
	scenes[2] = Scene::create("정도전5*5", "images3/정도전원본.png");

	//배경화면 생성
	//ScenePtr backgroundScene[3];
	backgroundScene[0] = Scene::create("타이타닉", "images1/타이타닉배경.png");
	backgroundScene[1] = Scene::create("티모", "images2/티모배경.png");
	backgroundScene[2] = Scene::create("정도전", "images3/정도전배경.png");


	//시작화면에 버튼 부착 
	//auto button1 = Object::create("images/타이타닉버튼.png", scene, 510, 400);
	auto button2 = Object::create("images2/티모버튼.png", scene, 540, 300);
	button2->setScale(0.4f);
	//auto button3 = Object::create("images/정도전버튼.png", scene, 520, 200);




	//버튼 누르면 각 해당하는 퍼즐 게임 화면으로 시작
	/*button1->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		scenes[0]->enter();
		return true;
		});*/
	button2->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		scenes[1]->enter();
		return true;
		});
	/*button3->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		scenes[2]->enter();
		return true;
		});*/


		//각 게임 마다 시작 버튼 부착 & 마우스 콜백 부착
	auto start1 = Object::create("images/start.png", scenes[0], 300, 300);
	start1->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		showMessage("게임시작");
		startGame1(backgroundScene[0], 0);
		return true;
		});
	auto start2 = Object::create("images/start.png", scenes[1], 300, 300);
	start2->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		showMessage("게임시작");
		startGame1(backgroundScene[1], 1);
		return true;
		});

	auto start3 = Object::create("images/start.png", scenes[2], 300, 300);
	start3->setOnMouseCallback([&](ObjectPtr o, int x, int y, MouseAction m)->bool {
		showMessage("게임시작");
		startGame1(backgroundScene[2], 2);
		return true;
		});
	startGame(scene);
}
