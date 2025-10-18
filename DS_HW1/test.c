#include <stdio.h>
#include <stdlib.h>

int memberNumber[1500000] = {0};

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int maxMemberNum = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &memberNumber[i]);
        if (memberNumber[i] > maxMemberNum) maxMemberNum = memberNumber[i];
    }

    // 統計每個人數出現次數
    int *count = calloc(maxMemberNum + 1, sizeof(int));
    for (int i = 0; i < N; i++) {
        count[memberNumber[i]]++;
    }

    // prefixCnt[i] = 到 i 為止總共有多少小隊
    // prefixSum[i] = 到 i 為止總共有多少人 (ai 的總和)
    int *prefixCnt = calloc(maxMemberNum + 1, sizeof(int));
    long long *prefixSum = calloc(maxMemberNum + 1, sizeof(long long));

    prefixCnt[0] = count[0];
    prefixSum[0] = (long long)count[0] * 0;

    for (int i = 1; i <= maxMemberNum; i++) {
        prefixCnt[i] = prefixCnt[i - 1] + count[i];
        prefixSum[i] = prefixSum[i - 1] + (long long)count[i] * i;
    }

    long long maxParticipants = 0;

    // 嘗試所有可能的隊伍大小 T
    for (int T = K; T <= maxMemberNum; T++) {
        long long total = 0;

        // 枚舉每個區間 [v*T, (v+1)*T-1]
        for (int v = 0; v * T <= maxMemberNum; v++) {
            int l = v * T;
            int r = (v + 1) * T - 1;
            if (r > maxMemberNum) r = maxMemberNum;

            // 區間內有多少小隊 (用 prefixCnt)
            int cnt = prefixCnt[r] - (l > 0 ? prefixCnt[l - 1] : 0);

            // 每個小隊能貢獻 v 個完整隊伍，每隊 T 人
            total += 1LL * cnt * v * T;
        }

        if (total > maxParticipants) maxParticipants = total;
    }

    printf("%lld\n", maxParticipants);
    return 0;
}
