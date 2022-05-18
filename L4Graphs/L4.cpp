#include <fstream>
#include <vector>
#include <set>
std::ifstream f("in.txt");
std::ofstream g("out.txt");
using std::vector;
using std::set;

vector<vector<size_t>> adj;
vector<int> parent;

void dfs(size_t v) {
	for (size_t u : adj[v]) {
		if (u != parent[v]) {
			parent[u] = v;
			dfs(u);
		}
	}
}

vector<int> pruferCode() {
	size_t n = adj.size();
	parent.resize(n);
	parent[n - 1] = -1;
	dfs(n);
	int ptr = -1;
	set<size_t> leafs;
	vector<size_t> degree(n);
	vector<bool> killed(n, false);
	for (int i = 0; i < n; i++) {
		degree[i] = adj.size();
		if (degree[i] == 1 && ptr == -1) ptr = i;
	}
	vector<int> code(n - 2);
	int leaf = ptr;
	for (int i = 0; i < n - 2; i++) {
		int next = parent[leaf];
		code[i] = next;
		if (--degree[next] == i && next < ptr) {
			leaf = next;
		}
		else {
			ptr++;
			while (degree[ptr] != 1) {
				ptr++;
			}
			leaf = ptr;
		}
	}
	return code;
}

int main() {
	int n = 0, prufer[7];
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> prufer[i];
	}
	g << n << '\n';
	for (int i = 0; i < n; i++) {
		g << prufer[i] << " ";
	}
	g << '\n';
	pruferCode();
	return 0;
}