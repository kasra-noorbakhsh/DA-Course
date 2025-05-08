#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main(){

    int n, m, r, a, b, c;
	int positive_infinity = std::numeric_limits<int>::max();
	int dist[100][100][100], dp[100][100][100];

    cin >> n >> m >> r;

	//taking input
    for(int i = 0; i < m; i++){
    	for(int j = 0; j < n; j++){
    		for(int k = 0; k < n; k++){
    			cin >> dist[i][j][k];
    		}
    	}
    }

	// this is for the floyd warshal algorithm
    for(int z = 0; z < m; z++){
    	for(int k = 0; k < n; k++){
    		for(int i = 0; i < n; i++){
    			for(int j = 0; j < n; j++){
    				dist[z][i][j] = min(dist[z][i][j], dist[z][i][k] + dist[z][k][j]);
    			}
    		}
    	}
    }

	//initialization
    for(int i = 0; i < n; i++){
    	for(int j = 0; j < n; j++){
    		dp[0][i][j] = dist[0][i][j];
    	}
	}

	//initialization
    for(int k = 1; k < m; k++){
    	for(int i = 0; i < n; i++){
    		for(int j = 0; j < n; j++){
    			dp[0][i][j] = min(dp[0][i][j], dist[k][i][j]);
    		}
    	}
    }

	//dp
    for(int z = 1; z < n; z++){
    	for(int i = 0; i < n; i++){
    		for(int j = 0; j < n; j++){
    			dp[z][i][j] = positive_infinity;
    			for (int k = 0; k < n; k++){
    				dp[z][i][j] = min(dp[z][i][j], dp[0][i][k] + dp[z - 1][k][j]);
    			}
    		}
    	}
    }

    for(int i = 0; i < r; i++){
		
    	cin >> a >> b >> c;

    	if(c > n-1){
    		c = n-1;
    	}

    	cout << dp[c][a-1][b-1] << endl;
	}

}