#include "renju.h"

int array[NUM][NUM];                    /* chessboard array */

int play(int x1, int y1, int *x2, int *y2)
{
	if(array[y1][x1]==EMPTY)
	{
		if(isIllegal(HUMAN, x1, y1)==1)
			return 3;
		array[y1][x1] = HUMAN;

		if(judge(COMPUTER, 4, x2, y2)==0)
			if(judge(HUMAN, 4, x2 , y2)==0)
				if(judge(COMPUTER, 3 , x2, y2)==0)
					if(judge(HUMAN, 3, x2 ,y2)==0)
						if(forcast(COMPUTER, 3, x2, y2)==0)
							if(forcast(HUMAN, 3, x2, y2)==0)
								if(forcast(COMPUTER, 2, x2, y2)==0)
									if(judge(COMPUTER, 2, x2, y2)==0)
										if(firstStep(x1 ,y1, x2, y2)==0)
											return -1;

		if(isWin(HUMAN))
			return HUMAN;
		if(isWin(COMPUTER))
			return COMPUTER;
		return 0;
	}
}

int isWin(int player)
{
	int i, j, drY, drX;

	for(i=0; i<NUM; i++)
		for(j=0; j<NUM; j++){
			if(array[i][j]!=player)	continue;
			for(drY=-1; drY<2; drY++)
				for(drX=-1; drX<2; drX++)
				{
					if(drY==0 && drX==0)
						continue;
					if( (i+drY*4)<0 || (i+drY*4)>=NUM \
									|| (j+drX*4)<0 || (j+drX*4)>=NUM )
						continue;

					int num, flag=0;
					for(num=1; num<5; num++)
					{
						if(array[i+drY*num][j+drX*num]==player)
							flag++;
						if(flag==4)
							return 1;
					}
				}
		}
	return 0;
}

int firstStep(int x1, int y1, int *x2, int *y2)
{
	int drY, drX;
	
	for(drY=-1; drY<2; drY++)
		for(drX=-1; drX<2; drX++){
			if(drY==0 && drX==0)	continue;
			if((y1+drY)>=0 && (y1+drY)<NUM \
						&& (x1+drX)>=0 && (x1+drX)<NUM \
						&& array[y1+drY][x1+drX]==EMPTY ){
				*y2 = y1+drY;
				*x2 = x1+drX;
				array[*y2][*x2] = COMPUTER;
				return 1;
			}
		}

	return 0;
}

int judge(int player, int num, int *x2, int *y2)
{
	int i, j, drY, drX, tmp, op;
	op = ((player==HUMAN) ? COMPUTER:HUMAN);

	for(i=0; i<NUM; i++)
		for(j=0; j<NUM; j++)
		{
			if(array[i][j]!=player)
				continue;
			if(judgePoint(player, num, 1, i, j, x2, y2)==1)
				return 1;
		}
		
	for(i=0; i<NUM; i++)
		for(j=0; j<NUM; j++)
		{
			if(array[i][j]!=player)
				continue;
			if(judgePoint(player, num, 3, i, j, x2, y2)==1)
				return 1;
		}
			
	return 0;
}

int judgePoint(int player, int num, int mode, int i, int j, int *x2, int *y2)
{
	int drY, drX, tmp, op;
	op = ((player==HUMAN) ? COMPUTER:HUMAN);
		
	for(drY=-1; drY<2; drY++)
		for(drX=-1; drX<2; drX++)
		{
			int rtn=0;
			if(drY==0 && drX==0)	continue;
		
			for(tmp=1; tmp<5; tmp++)
			if((i+drY*tmp)<0 || (i+drY*tmp)>=NUM \
							|| (j+drX*tmp)<0 || (j+drX*tmp)>=NUM \
							|| array[i+drY*tmp][j+drX*tmp]==op)
				rtn = 1;
		
			if(rtn==0)
			{
				int flag=0, count=1, k=1, cflag=0;
		
				for(tmp=1; tmp<=num; tmp++)
				{
					if((array[i+drY*tmp][j+drX*tmp]==player \
								|| (array[i+drY*tmp][j+drX*tmp]==EMPTY \
								&& flag==0 && ++flag)) \
								&& (flag==0 && (++count) || 1))
					{
						if(k==num)
						{
							if(((player==COMPUTER && num==2) \
											|| (player==HUMAN && num==3)) \
											&& (i-drY)>=0 && (i-drY)<NUM \
											&& (j-drX)>=0 && (j-drX)<NUM \
											&& array[i-drY][j-drX]!=op )
								cflag=1;
							if((player==COMPUTER && (num==3||num==4)) \
											||(player==HUMAN && num==4) )
								cflag=1;
		
							if(cflag==1){
								if(mode==1)
								{
									if(player==HUMAN)
									{
										if(judgePoint(op, 3, 2, i+drY*count, j+drX*count, x2, y2)==1 \
														|| judgePoint(op, 4, 2, i+drY*count, j+drX*count, x2, y2)==1)
										{
											*y2 = i+drY*count;
											*x2 = j+drX*count;
											array[*y2][*x2] = COMPUTER;
											return 1;
										}

										if(judgePoint(player, 3, 2, i+drY*count, j+drX*count, x2, y2)==1 \
														|| judgePoint(player, 4, 2, i+drY*count, j+drX*count, x2, y2)==1)
										{
											*y2 = i+drY*count;
											*x2 = j+drX*count;
											array[*y2][*x2] = COMPUTER;
											return 1;
										}
									}
								}
								if(mode==2)
										return 1;
								if(mode==3)
								{
									*y2 = i+drY*count;
									*x2 = j+drX*count;
									array[*y2][*x2] = COMPUTER;
									return 1;
								}
							}
						}
						k++;
					}
				}
			}
		}
	return 0;
}

int forcast(int player, int num, int *x2, int *y2)
{
	int i, j, drY, drX, tmp, op, fnum, dbflag;
	op = ((player==HUMAN) ? COMPUTER:HUMAN);

	for(i=0; i<NUM; i++)
		for(j=0; j<NUM; j++)
		{
			if(array[i][j]!=EMPTY)	continue;
			fnum = 0;
			dbflag = 0;

			for(drY=-1; drY<2; drY++)
				for(drX=-1; drX<2; drX++)
				{
					int rtn=0;
					if(drY==0 && drX==0)	continue;
					
					for(tmp=1; tmp<4; tmp++)
						if((i+drY*tmp)<0 || (i+drY*tmp)>=NUM \
									|| (j+drX*tmp)<0 || (j+drX*tmp)>=NUM \
									|| array[i+drY*tmp][j+drX*tmp]==op)
							rtn = 1;

					if(rtn==0)
					{
						int flag=0, count=1, k=1, cflag=0;

						for(tmp=1; tmp<=num; tmp++)
						{
							if((array[i+drY*tmp][j+drX*tmp]==player \
										|| (array[i+drY*tmp][j+drX*tmp]==EMPTY \
										&& flag==0 && ++flag)) \
										&& (flag==0 && (++count) || 1))
							{
								if(k==num \
												&& (i-drY)>=0 && (i-drY)<NUM \
												&& (j-drX)>=0 && (j-drX)<NUM \
												&& array[i-drY][j-drX]!=op )
								{
									if(count==3 && (i+drY*4)>=0 && (i+drY*4)>=NUM \
													&& (j+drX*4)>=0 && (j+drX*4)<NUM \
													&& array[i+drY*4][j+drX*4]==EMPTY)
										dbflag++;

									fnum++;
									if( findTwo(player ,i+drY*count, j+drX*count, drY, drX, x2, y2)==1)
										return 1;
								}
								k++;
							}
						}
					}
				}

			if(dbflag <2 &&fnum>1){
				*y2 = i;
				*x2 = j;
				array[*y2][*x2] = COMPUTER;
				return 1;
			}
		}
	return 0;
}

int findTwo(int player, int i, int j, int d1, int d2,int *x2, int *y2)
{
	int num=0, count, drY, drX, op;
	int dr[2][4]={{-1, -1, -1, 0}, \
								{-1, 0, 1, 1}};
	op = ((player==HUMAN) ? COMPUTER:HUMAN);

	for(count=0; count<4; count++){
		drY = dr[0][count];
		drX = dr[2][count];
		
		if((drY==d1 && drX==d2) || (-drY==d1 && -drX==d2))	continue;
		
		if( (i+drY)>=0 && (i+drY)<NUM \
						&& (j+drX)>=0 && (j+drX)<NUM \
						&& (i+drY)>=0 && (i+drY)<NUM \
						&& (j+drX)>=0 && (j+drX)<NUM \
						&& array[i+drY][j+drX]==player \
						&& array[i+drY][j+drX]!=op )
			if( (i-drY)>=0 && (i-drY)<NUM \
							&& (j-drX)>=0 && (j-drX)<NUM \
							&& (i-drY)>=0 && (i-drY)<NUM \
							&& (j-drX)>=0 && (j-drX)<NUM \
							&& array[i-drY][j-drX]==player \
							&& array[i-drY][j-drX]!=op )
				num++;
	}
	
	if(num>0){
		*y2 = i;
		*x2 = j;
		array[*y2][*x2] = COMPUTER;
		return 1;
	}

	return 0;
}

int isIllegal(int player, int j, int i)
{
	int drY, drX, tmp, op, dbflag;
	op = ((player==HUMAN) ? COMPUTER:HUMAN);

	dbflag = 0;

	for(drY=-1; drY<2; drY++)
		for(drX=-1; drX<2; drX++)
		{
			int rtn=0;
			if(drY==0 && drX==0)	continue;

			for(tmp=1; tmp<4; tmp++)
				if((i+drY*tmp)<0 || (i+drY*tmp)>=NUM \
								|| (j+drX*tmp)<0 || (j+drX*tmp)>=NUM \
								|| array[i+drY*tmp][j+drX*tmp]==op)
					rtn = 1;

			if((i+drY*4)<0 || (i+drY*4)>=NUM \
							|| (j+drX*4)<0 || (j+drX*4)>=NUM \
							|| array[i+drY*4][j+drX*4]!=EMPTY)
				rtn = 1;

			if(rtn==0)
			{
				int flag=0, count=1, k=1, cflag=0;

				if(array[i+drY][j+drX]==player \
								&& array[i+drY*2][j+drX*2]==player \
								&& (i-drY)>=0 && (i-drY)<NUM \
								&& (j-drX)>=0 && (j-drX)<NUM \
								&& array[i-drY][j-drX]==EMPTY)
					dbflag++;	
			}
		}

	if(dbflag>1)
		return 1;

	return 0;
}
