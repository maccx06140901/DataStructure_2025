#include <stdio.h>
#include <stdlib.h>

int memberNumber[1500000] = {0};

int main(){
    int N, K;
    scanf("%d %d", &N, &K);

    int maxMemberNum = 0;
    
    for(int i = 0; i < N ; i++){
        scanf("%d", &memberNumber[i]);
      
        if(memberNumber[i] > maxMemberNum) maxMemberNum = memberNumber[i];
    }

    int *count = calloc(maxMemberNum+1, sizeof(int));
    for(int i = 0; i < N; i++){
        count[memberNumber[i]]++;
    }

    long long int *prefixSum = calloc(maxMemberNum+1, sizeof(long long int));
    prefixSum[0] = 0;
    for(int i = 1; i < maxMemberNum+1; i++){
        prefixSum[i] = prefixSum[i-1] + (long long)count[i];
    }

    long long maxParticipants = 0;

    for(int T = K; T <= maxMemberNum; T++){//T:至少要T人，從T=K開始
        long long total = 0;

        for(int v = 1; v*T <= maxMemberNum; v++){//希望有v隊
            int l = v * T;
            int r = (v+1) * T - 1;
            //有v隊，代表人數在v*T~(v+1)*T-1之間，((v+1)*t就可以再組一隊了)
            if(r > maxMemberNum) r = maxMemberNum;

            int cnt  = prefixSum[r] - prefixSum[l - 1];//cnt是該區間有幾個大隊
            

            total += 1LL * cnt * v * T;//總人數+(cnt個大隊*v個小隊*一個小隊T人)
        }

        if(total > maxParticipants) maxParticipants = total;
    }

    printf("%lld\n", maxParticipants);
    return 0;
}