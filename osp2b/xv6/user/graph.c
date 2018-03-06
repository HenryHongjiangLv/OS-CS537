#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

struct pstat st;
int lowpid = 3, midpid = 4, highpid = 5;
int lowstart = 0, midstart = 0, highstart = 0;
int lowticks[200], midticks[200], highticks[200];
int totalticks[200];

void spin(int high_flag)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int total = 0;
  for(i = 0; i < 200; ++i)
    {
      for(j = 0; j < 2000000; ++j)
	{
	  k = j % 10;
	  k = k + 1;
	}
      total = 0;
      getpinfo(&st);
      for (l = 0; l < NPROC; l++){
	if (st.pid[l] == lowpid){
	  if (high_flag){
	    if (lowstart == 0)
	      lowstart = st.ticks[l];
	    else{
	      lowticks[i] = st.ticks[l] - lowstart;
	      total += lowticks[i];
	    }
	  }
	}
	else if (st.pid[l] == midpid){
	  if (high_flag){
	    if (midstart == 0)
	      midstart = st.ticks[l];
	    else{
	      midticks[i] = st.ticks[l] - midstart;
	      total += midticks[i];
	    }
	  }
	}
	else if (st.pid[l] == highpid){
	  if (high_flag) {
	    if (highstart == 0)
	      highstart = st.ticks[l];
	    else{
	      highticks[i] = st.ticks[l] - highstart;
	      total += highticks[i];
	    }
	  }
	}
      }
      totalticks[i] = total;
    }
}

void print(struct pstat *st)
{
  int i;
  for(i = 0; i < NPROC; i++) {
    if (st->inuse[i]) {
      printf(1, "pid: %d tickets: %d ticks: %d\n", st->pid[i], st->tickets[i], st->ticks[i]);
    }
  }
}

void print_arr(int* arr){
  int i = 0;
  for (i = 0; i < 200; i++){
    printf(1, "%d\n", arr[i]);
  }
}

int
main(int argc, char *argv[])
{
  int lowtickets = 10, midtickets = 20, hightickets = 30;
  struct pstat st_before, st_after;

  settickets(lowtickets);

  if(fork() == 0) // create first child process, with 20 tickets
    {
      settickets(midtickets);
      spin(0);
      exit();
    }

  if(fork() == 0)  // create first child process, with 20 tickets
    {
      settickets(hightickets);

      getpinfo(&st_before);
      printf(1, "\n ****PInfo before**** \n");
      print(&st_before);
      printf(1,"Spinning...\n");

      spin(1);

      printf(1, "low [pid %d]\n", lowpid);
      print_arr(lowticks);
      printf(1, "mid [pid %d]\n", midpid);
      print_arr(midticks);
      printf(1, "high [pid %d]\n", highpid);
      print_arr(highticks);
      printf(1, "total\n");
      print_arr(totalticks);

      getpinfo(&st_after);
      printf(1, "\n ****PInfo after**** \n");
      print(&st_after);


      exit();
    }

  spin(0);

  while (wait() > 0);
  exit();
}
