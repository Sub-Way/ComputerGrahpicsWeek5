# ComputerGrahpicsWeek5

## 5주차. 변환을 이용한 태양계 그리기

### 1.	첫번째 Cube를 만들고 그 무게중심으로 회전하기(20점)
-	첫번째 Cube 그리기: 10점
-	첫번째Cube 회전시키기: 10점

### 2.	두번째 Cube를 만들고 첫번째 Cube를 중심으로 회전하기(40점)
-	두번째 Cube 그리기: 10점
-	두번째 Cube 이동시키기: 10점
-	두번째 Cube의 무게중심으로 회전시키기: 10점
-	두번째 Cube 첫번째 Cube를 중심으로 회전시키기: 10점

### 3.	세번째 Cube를 만들고 두번째 Cube를 중심으로 회전하기(40점)
-	세번째 Cube 그리기: 10점
-	세번째 Cube 이동시키기: 10점
-	세번째 Cube 두번째 Cube를 중심으로 회전시키기: 10점
-	모든 Cube의 크기가 다르게 만들기: 10점

Hint. glPushMatrix()와 glPopMatrix()를 사용하세요. 
glPushMatrix()는 현재상태의 변환행렬을 스택에 저장해 놓았다가 glPopMatrix()를 호출시키면 이전 상태로 되돌려 놓는다. 이를 이용하면 glPushMatrix()와 glPopMatrix() 사이에서 특정 모델만 변환이 되도록 만들 수 있다.


![image](https://user-images.githubusercontent.com/22046757/61995177-a4b3ce00-b0bf-11e9-9a0e-9d7b1b4238bf.png)


참고 동영상: https://youtu.be/2W4i1kVYBhg 

### 1. 첫번째 Cube를 만들고 그 무게중심으로 회전하기
~~~
		//첫번째 Cube
		glPushMatrix();
		glRotated(i, 1, 1, 1);
		drawCube(0.07, 0.07, 0.07);
		glPopMatrix();
~~~
![image](https://user-images.githubusercontent.com/22046757/61995701-c795b080-b0c6-11e9-80e0-85a2d9857b23.png)

drawCube함수를 통해 첫번째 Cube를 생성하였다.  0.07의 큐브가 생성되었다. 그리고 glRotated 함수를 이용해 무게중심으로 회전하도록 만들었다. glPushMatrix함수로 변환된 좌표축을 저장하고 1번을 수행한 후, glPopMatrix를 통해 변환된 좌표축을 꺼낸다.

### 2. 두번째 Cube를 만들고 첫번째 Cube를 중심으로 회전하기
~~~
//두번째 Cube
		glPushMatrix();
		glRotated(i, 0, 1, 0);
		glTranslated(0.3, 0, 0);
		glPushMatrix();
		glRotated(i, 1, 1, 1);
		drawCube(0.05, 0.05, 0.05);
		glPopMatrix();
~~~
![image](https://user-images.githubusercontent.com/22046757/61995704-c95f7400-b0c6-11e9-9080-b62414b6084d.png)

glPushMatrix함수를 두 번 사용하였다. 두번째 glPushMatrix함수 안에서 glRotated 함수를 이용해서 자신의 무게중심으로 회전하도록 만들었다. 그리고 첫번째 glPushMatrix함수 안에서 x축으로 0.3만큼 이동시키고 y축을 중심(첫번째 Cube 중심)으로 회전하도록 하였다. 실행 화면을 위해서 glPopMatrix를 두 번 사용하였지만 실제로는 세번째 Cube를 위해 glPopMatrix는 한번만 사용해서 변환된 좌표축을 남겨놓았다.

### 3. 세번째 Cube를 만들고 두번째 Cube를 중심으로 회전하기
~~~
		//세번째 Cube
		glPushMatrix();
		glRotated(i*3, 0.0, 1.0, 0.0);
		glTranslated(0.1, 0, 0);
		drawCube(0.01, 0.01, 0.01);
		glPopMatrix();
		glPopMatrix();
~~~
![image](https://user-images.githubusercontent.com/22046757/61995706-ca90a100-b0c6-11e9-8d2d-c8a495e26773.png)

glPopMatrix를 한번만 했기 때문에 두번째 Cube에 대한 변환된 축 정보가 남아있다. 때문에 glPushMatrix 함수를 한번만 사용해서 두번째 Cube를 중심으로 회전시키는 것이 가능하다. glTranslated 함수로 두번째 축을 기준으로 x축으로 0.1만큼 이동시킨 새로운 축을 생성하고 glRoatated 함수를 통해서 회전을 하도록 만들었다. 자연스러운 회전을 위해 세번째 Cube의 속도를 기존보다 2배 빠르게 하였다.
