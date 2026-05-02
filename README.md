[index.html](https://github.com/user-attachments/files/27299735/index.html)
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8"/>
<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
<title>Delhi–Dehradun Expressway | DSA Simulation</title>
<link href="https://fonts.googleapis.com/css2?family=Syne:wght@400;600;700;800&family=JetBrains+Mono:wght@400;500&display=swap" rel="stylesheet"/>
<style>
:root {
  --bg: #0a0d12;
  --bg2: #0f1318;
  --bg3: #151b24;
  --border: rgba(255,255,255,0.07);
  --border2: rgba(255,255,255,0.13);
  --accent: #00e5a0;
  --accent2: #0098ff;
  --accent3: #ff6b35;
  --accent4: #ffd700;
  --text: #e8edf4;
  --muted: #6b7a8d;
  --muted2: #8fa3b8;
  --font: 'Syne', sans-serif;
  --mono: 'JetBrains Mono', monospace;
  --radius: 12px;
  --radius2: 20px;
}
*{margin:0;padding:0;box-sizing:border-box}
html{scroll-behavior:smooth}
body{background:var(--bg);color:var(--text);font-family:var(--font);min-height:100vh;overflow-x:hidden}

/* NOISE OVERLAY */
body::before{content:'';position:fixed;inset:0;background-image:url("data:image/svg+xml,%3Csvg viewBox='0 0 256 256' xmlns='http://www.w3.org/2000/svg'%3E%3Cfilter id='n'%3E%3CfeTurbulence type='fractalNoise' baseFrequency='0.9' numOctaves='4' stitchTiles='stitch'/%3E%3C/filter%3E%3Crect width='100%25' height='100%25' filter='url(%23n)' opacity='0.04'/%3E%3C/svg%3E");opacity:0.4;pointer-events:none;z-index:0}

/* GRID LINES BG */
.grid-bg{position:fixed;inset:0;background-image:linear-gradient(rgba(0,229,160,0.03) 1px,transparent 1px),linear-gradient(90deg,rgba(0,229,160,0.03) 1px,transparent 1px);background-size:60px 60px;pointer-events:none;z-index:0}

/* NAV */
nav{position:fixed;top:0;left:0;right:0;z-index:100;display:flex;align-items:center;justify-content:space-between;padding:18px 40px;background:rgba(10,13,18,0.85);backdrop-filter:blur(16px);border-bottom:1px solid var(--border)}
.nav-logo{font-size:13px;font-family:var(--mono);color:var(--accent);letter-spacing:0.08em}
.nav-links{display:flex;gap:32px}
.nav-links a{font-size:12px;color:var(--muted);text-decoration:none;letter-spacing:0.06em;transition:color .2s}
.nav-links a:hover{color:var(--accent)}
.nav-badge{font-size:11px;font-family:var(--mono);padding:4px 10px;border:1px solid var(--accent);border-radius:20px;color:var(--accent)}

/* HERO */
.hero{position:relative;z-index:1;min-height:100vh;display:flex;flex-direction:column;align-items:center;justify-content:center;padding:120px 40px 80px;text-align:center;overflow:hidden}
.hero-tag{font-size:11px;font-family:var(--mono);color:var(--accent);letter-spacing:0.15em;margin-bottom:24px;display:inline-flex;align-items:center;gap:8px}
.hero-tag::before,.hero-tag::after{content:'';width:32px;height:1px;background:var(--accent);opacity:0.5}
.hero h1{font-size:clamp(42px,7vw,88px);font-weight:800;line-height:0.95;letter-spacing:-0.03em;margin-bottom:28px}
.hero h1 .line1{display:block;color:var(--text)}
.hero h1 .line2{display:block;color:var(--accent);position:relative}
.hero h1 .line3{display:block;color:var(--muted);font-size:0.6em;font-weight:400;letter-spacing:0.02em;margin-top:8px}
.hero-desc{max-width:560px;font-size:15px;color:var(--muted2);line-height:1.7;margin-bottom:48px}
.hero-btns{display:flex;gap:14px;flex-wrap:wrap;justify-content:center}
.btn-primary{padding:14px 32px;background:var(--accent);color:#000;border:none;border-radius:var(--radius);font-family:var(--font);font-size:14px;font-weight:700;cursor:pointer;transition:transform .15s,box-shadow .15s;letter-spacing:0.04em}
.btn-primary:hover{transform:translateY(-2px);box-shadow:0 8px 32px rgba(0,229,160,0.35)}
.btn-secondary{padding:14px 32px;background:transparent;color:var(--text);border:1px solid var(--border2);border-radius:var(--radius);font-family:var(--font);font-size:14px;font-weight:600;cursor:pointer;transition:all .2s;letter-spacing:0.04em}
.btn-secondary:hover{border-color:var(--accent2);color:var(--accent2)}

/* ROAD ANIMATION */
.road-anim{position:absolute;bottom:0;left:0;right:0;height:160px;overflow:hidden;pointer-events:none}
.road-line{height:3px;background:linear-gradient(90deg,transparent,var(--accent),transparent);animation:roadmove 2.5s linear infinite;opacity:0.3}
.road-line:nth-child(2){animation-delay:0.8s;opacity:0.15;margin-top:40px}
.road-line:nth-child(3){animation-delay:1.6s;opacity:0.1;margin-top:80px}
@keyframes roadmove{0%{transform:translateX(-100%)}100%{transform:translateX(100%)}}

/* STATS BAR */
.stats-bar{position:relative;z-index:1;display:grid;grid-template-columns:repeat(4,1fr);gap:1px;background:var(--border);border-top:1px solid var(--border);border-bottom:1px solid var(--border)}
.stat-item{background:var(--bg2);padding:28px 32px;text-align:center}
.stat-num{font-size:36px;font-weight:800;color:var(--accent);font-family:var(--mono);display:block;margin-bottom:4px}
.stat-lbl{font-size:11px;color:var(--muted);letter-spacing:0.1em}

/* SECTION */
section{position:relative;z-index:1;padding:80px 40px;max-width:1200px;margin:0 auto}
.section-tag{font-size:11px;font-family:var(--mono);color:var(--accent);letter-spacing:0.15em;margin-bottom:16px;display:flex;align-items:center;gap:10px}
.section-tag::after{content:'';flex:1;height:1px;background:var(--border)}
.section-title{font-size:clamp(28px,4vw,48px);font-weight:800;letter-spacing:-0.02em;margin-bottom:14px}
.section-sub{font-size:15px;color:var(--muted2);line-height:1.7;max-width:600px;margin-bottom:48px}

/* ── GRAPH VISUALIZER ── */
.viz-container{background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius2);overflow:hidden}
.viz-header{padding:20px 28px;border-bottom:1px solid var(--border);display:flex;align-items:center;justify-content:space-between;flex-wrap:gap}
.viz-title{font-size:14px;font-weight:600;color:var(--muted2)}
.algo-tabs{display:flex;gap:6px;flex-wrap:wrap}
.algo-tab{padding:7px 16px;border:1px solid var(--border);border-radius:30px;font-size:12px;font-family:var(--mono);background:transparent;color:var(--muted);cursor:pointer;transition:all .2s;letter-spacing:0.04em}
.algo-tab:hover{border-color:var(--border2);color:var(--text)}
.algo-tab.active{background:var(--accent);color:#000;border-color:var(--accent);font-weight:600}
.algo-tab.blue.active{background:var(--accent2);border-color:var(--accent2)}
.algo-tab.orange.active{background:var(--accent3);border-color:var(--accent3)}
.algo-tab.gold.active{background:var(--accent4);color:#000;border-color:var(--accent4)}

.viz-body{display:grid;grid-template-columns:1fr 320px;min-height:460px}
.canvas-wrap{position:relative;background:var(--bg3);border-right:1px solid var(--border)}
canvas{display:block;width:100%;height:100%}
.viz-panel{padding:24px;display:flex;flex-direction:column;gap:16px}

.panel-label{font-size:10px;font-family:var(--mono);color:var(--muted);letter-spacing:0.12em;margin-bottom:8px}
.route-controls{display:flex;flex-direction:column;gap:10px}
select.route-sel{width:100%;padding:10px 14px;background:var(--bg3);border:1px solid var(--border2);border-radius:var(--radius);color:var(--text);font-family:var(--mono);font-size:12px;cursor:pointer;outline:none;appearance:none}
select.route-sel:focus{border-color:var(--accent)}
.mode-btns{display:flex;gap:6px}
.mode-btn{flex:1;padding:7px 4px;font-size:11px;font-family:var(--mono);border:1px solid var(--border);border-radius:8px;background:var(--bg3);color:var(--muted);cursor:pointer;transition:all .2s}
.mode-btn.active{border-color:var(--accent);color:var(--accent);background:rgba(0,229,160,0.08)}
.run-btn{width:100%;padding:12px;background:var(--accent);color:#000;border:none;border-radius:var(--radius);font-family:var(--font);font-size:13px;font-weight:700;cursor:pointer;letter-spacing:0.05em;transition:all .2s}
.run-btn:hover{box-shadow:0 4px 20px rgba(0,229,160,0.4);transform:translateY(-1px)}
.result-card{background:var(--bg3);border:1px solid var(--border);border-radius:var(--radius);padding:14px;flex:1;overflow-y:auto}
.res-metric{display:flex;justify-content:space-between;align-items:center;padding:6px 0;border-bottom:1px solid var(--border)}
.res-metric:last-child{border:none}
.res-key{font-size:11px;color:var(--muted);font-family:var(--mono)}
.res-val{font-size:13px;font-weight:600;font-family:var(--mono);color:var(--accent)}
.path-chips{display:flex;flex-wrap:wrap;gap:5px;margin-top:10px}
.path-chip{padding:4px 10px;border-radius:20px;font-size:11px;font-family:var(--mono);background:rgba(0,229,160,0.1);border:1px solid rgba(0,229,160,0.25);color:var(--accent)}
.path-chip.src-chip{background:rgba(255,215,0,0.1);border-color:rgba(255,215,0,0.3);color:var(--accent4)}
.path-chip.dst-chip{background:rgba(255,107,53,0.1);border-color:rgba(255,107,53,0.3);color:var(--accent3)}
.arrow-chip{color:var(--muted);font-size:11px;align-self:center}

/* ── DSA CARDS ── */
.dsa-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(340px,1fr));gap:16px}
.dsa-card{background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius2);padding:28px;transition:border-color .2s,transform .2s;cursor:pointer;position:relative;overflow:hidden}
.dsa-card::before{content:'';position:absolute;top:0;left:0;right:0;height:2px;background:var(--card-accent,var(--accent));opacity:0.6}
.dsa-card:hover{border-color:var(--border2);transform:translateY(-3px)}
.card-num{font-size:11px;font-family:var(--mono);color:var(--muted);letter-spacing:0.12em;margin-bottom:12px}
.card-title{font-size:20px;font-weight:700;margin-bottom:6px;color:var(--text)}
.card-sub{font-size:12px;font-family:var(--mono);color:var(--card-accent,var(--accent));margin-bottom:14px;letter-spacing:0.04em}
.card-desc{font-size:13px;color:var(--muted2);line-height:1.65;margin-bottom:16px}
.card-complexity{display:flex;gap:8px;flex-wrap:wrap}
.complexity-badge{font-size:11px;font-family:var(--mono);padding:4px 10px;border-radius:20px;background:rgba(255,255,255,0.05);border:1px solid var(--border2);color:var(--muted2)}

/* ── TOLL SYSTEM ── */
.toll-section{background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius2);overflow:hidden}
.toll-header{padding:20px 28px;border-bottom:1px solid var(--border);display:flex;align-items:center;justify-content:space-between}
.toll-title{font-size:15px;font-weight:700}
.toll-body{padding:24px;display:grid;grid-template-columns:1fr 1fr;gap:24px}
.toll-vehicle-check{display:flex;flex-direction:column;gap:12px}
.toll-input{display:flex;gap:8px}
.v-input{flex:1;padding:10px 14px;background:var(--bg3);border:1px solid var(--border2);border-radius:var(--radius);color:var(--text);font-family:var(--mono);font-size:12px;outline:none}
.v-input:focus{border-color:var(--accent)}
.v-btn{padding:10px 18px;background:var(--accent);color:#000;border:none;border-radius:var(--radius);font-family:var(--mono);font-size:12px;font-weight:700;cursor:pointer}
.bloom-result{padding:12px 16px;border-radius:var(--radius);font-size:12px;font-family:var(--mono);display:none}
.bloom-result.show{display:block}
.bloom-result.yes{background:rgba(0,229,160,0.1);border:1px solid rgba(0,229,160,0.3);color:var(--accent)}
.bloom-result.no{background:rgba(255,107,53,0.1);border:1px solid rgba(255,107,53,0.3);color:var(--accent3)}
.registered-list{display:flex;flex-direction:column;gap:6px}
.v-tag{font-size:11px;font-family:var(--mono);padding:6px 12px;background:var(--bg3);border:1px solid var(--border);border-radius:8px;color:var(--muted2);cursor:pointer;transition:all .2s}
.v-tag:hover{border-color:var(--accent);color:var(--accent)}

/* ── FENWICK TABLE ── */
.fenwick-section{background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius2);overflow:hidden}
.fenwick-body{padding:24px}
.fenwick-bars{display:flex;align-items:flex-end;gap:8px;height:160px;margin-bottom:16px}
.f-bar-wrap{flex:1;display:flex;flex-direction:column;align-items:center;gap:5px}
.f-bar{width:100%;border-radius:4px 4px 0 0;transition:all .4s;min-height:4px;position:relative}
.f-label{font-size:9px;font-family:var(--mono);color:var(--muted);text-align:center;line-height:1.3}
.f-val{font-size:9px;font-family:var(--mono);color:var(--accent);text-align:center}
.fenwick-query{display:flex;gap:10px;align-items:center;flex-wrap:wrap;margin-top:16px;padding-top:16px;border-top:1px solid var(--border)}
.q-label{font-size:12px;font-family:var(--mono);color:var(--muted2)}
.range-inputs{display:flex;gap:8px;align-items:center}
.r-inp{width:60px;padding:7px 10px;background:var(--bg3);border:1px solid var(--border2);border-radius:var(--radius);font-family:var(--mono);font-size:12px;color:var(--text);outline:none;text-align:center}
.q-btn{padding:7px 16px;background:var(--accent2);color:#fff;border:none;border-radius:var(--radius);font-family:var(--mono);font-size:12px;cursor:pointer}
.q-result{font-size:14px;font-family:var(--mono);color:var(--accent4);font-weight:600}

/* ── MST VIZ ── */
.mst-section{background:var(--bg2);border:1px solid var(--border);border-radius:var(--radius2);overflow:hidden}
.mst-body{padding:24px;display:grid;grid-template-columns:1fr 1fr;gap:24px}
.mst-canvas-wrap{background:var(--bg3);border-radius:var(--radius);overflow:hidden}
.mst-edges{display:flex;flex-direction:column;gap:8px}
.mst-edge-row{display:flex;align-items:center;gap:10px;padding:10px 14px;background:var(--bg3);border-radius:var(--radius);border:1px solid var(--border);font-size:12px;font-family:var(--mono)}
.mst-edge-row.in-mst{border-color:rgba(0,229,160,0.4);background:rgba(0,229,160,0.05)}
.edge-cities{flex:1;color:var(--muted2)}
.edge-dist{color:var(--accent);font-weight:600}
.mst-badge{font-size:10px;padding:2px 8px;border-radius:10px;background:var(--accent);color:#000;font-weight:700}

/* ── FOOTER ── */
footer{position:relative;z-index:1;border-top:1px solid var(--border);padding:40px;text-align:center}
.footer-logo{font-size:24px;font-weight:800;color:var(--accent);margin-bottom:8px}
.footer-sub{font-size:12px;color:var(--muted);font-family:var(--mono)}

/* ANIMATIONS */
@keyframes fadeUp{from{opacity:0;transform:translateY(24px)}to{opacity:1;transform:translateY(0)}}
.fade-up{animation:fadeUp .6s ease both}
.delay-1{animation-delay:.1s}.delay-2{animation-delay:.2s}.delay-3{animation-delay:.3s}.delay-4{animation-delay:.4s}

@keyframes pulse-dot{0%,100%{opacity:1}50%{opacity:0.3}}
.live-dot{width:6px;height:6px;border-radius:50%;background:var(--accent);display:inline-block;animation:pulse-dot 1.5s ease infinite}

/* MOBILE */
@media(max-width:768px){
  nav{padding:16px 20px}
  .nav-links{display:none}
  section{padding:60px 20px}
  .stats-bar{grid-template-columns:repeat(2,1fr)}
  .viz-body{grid-template-columns:1fr}
  .canvas-wrap{min-height:280px}
  .toll-body,.mst-body{grid-template-columns:1fr}
  .hero{padding:100px 20px 60px}
}
</style>
</head>
<body>
<div class="grid-bg"></div>

<!-- NAV -->
<nav>
  <div class="nav-logo">// NH-334B · DSA SIMULATION</div>
  <div class="nav-links">
    <a href="#visualizer">Visualizer</a>
    <a href="#algorithms">Algorithms</a>
    <a href="#toll">Toll System</a>
    <a href="#mst">MST</a>
  </div>
  <div class="nav-badge"><span class="live-dot"></span> LIVE</div>
</nav>

<!-- HERO -->
<div class="hero">
  <div class="hero-tag">ADVANCED DSA PROJECT</div>
  <h1>
    <span class="line1 fade-up">DELHI–</span>
    <span class="line2 fade-up delay-1">DEHRADUN</span>
    <span class="line3 fade-up delay-2">Expressway Navigation Simulation</span>
  </h1>
  <p class="hero-desc fade-up delay-3">
    A complete simulation of a smart highway system using Graph Theory, Dijkstra, Bellman-Ford, Kruskal's MST, Fenwick Tree, Bloom Filter, and more — built entirely in C++.
  </p>
  <div class="hero-btns fade-up delay-4">
    <button class="btn-primary" onclick="document.getElementById('visualizer').scrollIntoView({behavior:'smooth'})">Launch Visualizer</button>
    <button class="btn-secondary" onclick="document.getElementById('algorithms').scrollIntoView({behavior:'smooth'})">View Algorithms</button>
  </div>
  <div class="road-anim">
    <div class="road-line"></div>
    <div class="road-line"></div>
    <div class="road-line"></div>
  </div>
</div>

<!-- STATS -->
<div class="stats-bar">
  <div class="stat-item"><span class="stat-num" id="cnt-nodes">0</span><span class="stat-lbl">GRAPH NODES</span></div>
  <div class="stat-item"><span class="stat-num" id="cnt-edges">0</span><span class="stat-lbl">GRAPH EDGES</span></div>
  <div class="stat-item"><span class="stat-num" id="cnt-algos">0</span><span class="stat-lbl">ALGORITHMS</span></div>
  <div class="stat-item"><span class="stat-num" id="cnt-km">0</span><span class="stat-lbl">TOTAL KM</span></div>
</div>

<!-- GRAPH VISUALIZER -->
<section id="visualizer">
  <div class="section-tag">01 · GRAPH VISUALIZER</div>
  <h2 class="section-title">Route Finder</h2>
  <p class="section-sub">Interact with the expressway graph. Select source & destination, pick an algorithm, and watch the optimal path animate in real-time.</p>

  <div class="viz-container">
    <div class="viz-header">
      <span class="viz-title">Expressway Graph — Adjacency List</span>
      <div class="algo-tabs">
        <button class="algo-tab active" data-mode="0" onclick="setMode(0,this)">Dijkstra · Distance</button>
        <button class="algo-tab blue" data-mode="1" onclick="setMode(1,this)">Dijkstra · Time</button>
        <button class="algo-tab orange" data-mode="2" onclick="setMode(2,this)">Dijkstra · Toll</button>
        <button class="algo-tab" data-mode="3" onclick="setMode(3,this)">BFS · Stops</button>
        <button class="algo-tab gold" data-mode="4" onclick="setMode(4,this)">DFS · All Routes</button>
      </div>
    </div>
    <div class="viz-body">
      <div class="canvas-wrap">
        <canvas id="mainCanvas"></canvas>
      </div>
      <div class="viz-panel">
        <div>
          <div class="panel-label">SOURCE</div>
          <select class="route-sel" id="srcSel"></select>
        </div>
        <div>
          <div class="panel-label">DESTINATION</div>
          <select class="route-sel" id="dstSel"></select>
        </div>
        <div>
          <div class="panel-label">WEIGHT MODE</div>
          <div class="mode-btns">
            <button class="mode-btn active" id="mb0" onclick="setMode(0,document.querySelector('.algo-tab'))">dist</button>
            <button class="mode-btn" id="mb1" onclick="setMode(1,document.querySelectorAll('.algo-tab')[1])">time</button>
            <button class="mode-btn" id="mb2" onclick="setMode(2,document.querySelectorAll('.algo-tab')[2])">toll</button>
          </div>
        </div>
        <button class="run-btn" onclick="runAlgo()">▶ RUN ALGORITHM</button>
        <div class="result-card" id="resultCard">
          <div style="color:var(--muted);font-size:12px;font-family:var(--mono)">Select nodes and run algorithm...</div>
        </div>
      </div>
    </div>
  </div>
</section>

<!-- ALGORITHMS -->
<section id="algorithms">
  <div class="section-tag">02 · ALGORITHMS</div>
  <h2 class="section-title">DSA Concepts Used</h2>
  <p class="section-sub">Eight advanced data structures and algorithms working together to simulate a real-world highway management system.</p>

  <div class="dsa-grid">
    <div class="dsa-card" style="--card-accent:#00e5a0">
      <div class="card-num">01 ·</div>
      <div class="card-title">Graph</div>
      <div class="card-sub">Adjacency List + Hashing</div>
      <div class="card-desc">Cities are nodes, roads are weighted edges with distance, time, and toll. Unordered_map provides O(1) city name lookup.</div>
      <div class="card-complexity"><span class="complexity-badge">Space O(V+E)</span><span class="complexity-badge">Lookup O(1)</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#0098ff">
      <div class="card-num">02 ·</div>
      <div class="card-title">Dijkstra</div>
      <div class="card-sub">Min-Heap Priority Queue</div>
      <div class="card-desc">Finds shortest path by distance, time, or toll using a greedy approach with a priority queue. Handles non-negative weights.</div>
      <div class="card-complexity"><span class="complexity-badge">O(E log V)</span><span class="complexity-badge">Greedy</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#ff6b35">
      <div class="card-num">03 ·</div>
      <div class="card-title">Bellman-Ford</div>
      <div class="card-sub">Negative Cycle Detection</div>
      <div class="card-desc">Detects fuel arbitrage opportunities — negative weight cycles where a route can generate infinite savings.</div>
      <div class="card-complexity"><span class="complexity-badge">O(V·E)</span><span class="complexity-badge">DP-based</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#ffd700">
      <div class="card-num">04 ·</div>
      <div class="card-title">Kruskal + DSU</div>
      <div class="card-sub">Minimum Spanning Tree</div>
      <div class="card-desc">Finds the minimum-cost road network connecting all cities. Disjoint Set Union detects cycles in O(α(n)) — nearly constant time.</div>
      <div class="card-complexity"><span class="complexity-badge">O(E log E)</span><span class="complexity-badge">Union-Find</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#b388ff">
      <div class="card-num">05 ·</div>
      <div class="card-title">Fenwick Tree</div>
      <div class="card-sub">Binary Indexed Tree</div>
      <div class="card-desc">Supports O(log N) range sum queries and point updates on toll collection data — ideal for real-time revenue tracking.</div>
      <div class="card-complexity"><span class="complexity-badge">Query O(log N)</span><span class="complexity-badge">Update O(log N)</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#40e0d0">
      <div class="card-num">06 ·</div>
      <div class="card-title">Bloom Filter</div>
      <div class="card-sub">Probabilistic Data Structure</div>
      <div class="card-desc">Checks if a vehicle has passed a toll plaza using three hash functions and a bitset. O(1) time, no false negatives.</div>
      <div class="card-complexity"><span class="complexity-badge">O(1) lookup</span><span class="complexity-badge">O(m) space</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#ff8a80">
      <div class="card-num">07 ·</div>
      <div class="card-title">Max-Heap</div>
      <div class="card-sub">Priority Queue</div>
      <div class="card-desc">Powers Top-K toll plaza queries. The highest-revenue plazas bubble to the top efficiently using STL priority_queue.</div>
      <div class="card-complexity"><span class="complexity-badge">O(K log N)</span><span class="complexity-badge">Top-K queries</span></div>
    </div>
    <div class="dsa-card" style="--card-accent:#69f0ae">
      <div class="card-num">08 ·</div>
      <div class="card-title">BFS / DFS</div>
      <div class="card-sub">Graph Traversal</div>
      <div class="card-desc">BFS finds paths with fewest stops (unweighted). DFS with backtracking enumerates all possible routes from source to destination.</div>
      <div class="card-complexity"><span class="complexity-badge">BFS O(V+E)</span><span class="complexity-badge">DFS O(V+E)</span></div>
    </div>
  </div>
</section>

<!-- TOLL SYSTEM -->
<section id="toll" style="padding-top:0">
  <div class="section-tag">03 · TOLL MANAGEMENT</div>
  <h2 class="section-title">Bloom Filter · Vehicle Check</h2>
  <p class="section-sub">Probabilistic O(1) vehicle lookup — check if any vehicle has passed a toll plaza. Zero false negatives guaranteed.</p>

  <div class="toll-section">
    <div class="toll-header">
      <span class="toll-title">Toll Plaza — Vehicle Registry</span>
      <span style="font-size:12px;font-family:var(--mono);color:var(--muted)">bitset[1024] · 3 hash functions</span>
    </div>
    <div class="toll-body">
      <div class="toll-vehicle-check">
        <div class="panel-label">CHECK VEHICLE</div>
        <div class="toll-input">
          <input class="v-input" id="vInput" placeholder="e.g. DL01AB1234" maxlength="12"/>
          <button class="v-btn" onclick="checkVehicle()">CHECK</button>
        </div>
        <div class="bloom-result" id="bloomResult"></div>
        <div style="margin-top:8px">
          <div class="panel-label">REGISTERED VEHICLES (click to auto-fill)</div>
          <div class="registered-list" id="regList"></div>
        </div>
      </div>
      <div>
        <div class="panel-label">FENWICK TREE · TOLL REVENUE</div>
        <div class="fenwick-bars" id="fBars"></div>
        <div style="font-size:11px;font-family:var(--mono);color:var(--muted);margin-bottom:12px">Daily collections per plaza (₹)</div>
        <div class="fenwick-query">
          <span class="q-label">Range sum [</span>
          <div class="range-inputs">
            <input class="r-inp" id="qL" value="0" type="number" min="0"/>
            <span class="q-label">to</span>
            <input class="r-inp" id="qR" value="4" type="number" min="0"/>
          </div>
          <span class="q-label">]</span>
          <button class="q-btn" onclick="fenwickQuery()">QUERY</button>
          <span class="q-result" id="qResult"></span>
        </div>
      </div>
    </div>
  </div>
</section>

<!-- MST -->
<section id="mst" style="padding-top:0">
  <div class="section-tag">04 · MINIMUM SPANNING TREE</div>
  <h2 class="section-title">Kruskal's Algorithm + DSU</h2>
  <p class="section-sub">Find the minimum-cost road network that connects all cities. Green edges form the MST — the optimal infrastructure plan.</p>

  <div class="mst-section">
    <div class="toll-header">
      <span class="toll-title">MST — Minimum Road Network</span>
      <span style="font-size:12px;font-family:var(--mono);color:var(--accent)">Total MST weight: <span id="mstTotal">—</span> km</span>
    </div>
    <div class="mst-body">
      <div class="mst-canvas-wrap"><canvas id="mstCanvas" style="width:100%;display:block"></canvas></div>
      <div>
        <div class="panel-label">EDGES (sorted by distance)</div>
        <div class="mst-edges" id="mstEdgeList"></div>
      </div>
    </div>
  </div>
</section>

<!-- FOOTER -->
<footer>
  <div class="footer-logo">NH-334B</div>
  <div class="footer-sub">Delhi–Dehradun Expressway · Advanced DSA Simulation · C++ Implementation</div>
  <div style="margin-top:16px;font-size:11px;font-family:var(--mono);color:var(--muted)">
    Graph · Dijkstra · Bellman-Ford · Kruskal · Fenwick Tree · Bloom Filter · Heap · Hashing
  </div>
</footer>

<script>
// ── DATA ──────────────────────────────────────
const CITIES = ["Delhi","Baghpat","Shamli","Saharanpur","Dehradun"];
const KM_FROM_DELHI = [0,47,77,122,192];
const EDGES_RAW = [
  [0,1,47,40,60],
  [1,2,30,25,40],
  [2,3,45,35,60],
  [3,4,70,60,100],
  [0,3,170,130,180]
];

const N = CITIES.length;
const ADJ = Array.from({length:N},()=>[]);
EDGES_RAW.forEach(([u,v,d,t,toll])=>{
  ADJ[u].push({to:v,dist:d,time:t,toll});
  ADJ[v].push({to:u,dist:d,time:t,toll});
});

// Canvas node positions (relative, will be scaled)
const POSITIONS = [
  {x:0.08,y:0.5},
  {x:0.28,y:0.28},
  {x:0.46,y:0.18},
  {x:0.65,y:0.38},
  {x:0.9,y:0.65}
];

let currentMode = 0;
let currentPath = [];
let animFrame = 0;

// ── GRAPH CANVAS ──────────────────────────────
const canvas = document.getElementById('mainCanvas');
const ctx = canvas.getContext('2d');

function resizeCanvas(){
  const wrap = canvas.parentElement;
  canvas.width = wrap.offsetWidth;
  canvas.height = Math.max(400, wrap.offsetHeight || 400);
  drawGraph();
}

function nodePos(i){
  return {
    x: POSITIONS[i].x * canvas.width,
    y: POSITIONS[i].y * canvas.height
  };
}

function drawGraph(highlightPath=[], animProgress=1){
  const c = ctx;
  c.clearRect(0,0,canvas.width,canvas.height);
  // subtle grid
  c.strokeStyle='rgba(255,255,255,0.03)';
  c.lineWidth=1;
  for(let x=0;x<canvas.width;x+=40){c.beginPath();c.moveTo(x,0);c.lineTo(x,canvas.height);c.stroke()}
  for(let y=0;y<canvas.height;y+=40){c.beginPath();c.moveTo(0,y);c.lineTo(canvas.width,y);c.stroke()}

  const pathSet = new Set();
  for(let i=0;i+1<highlightPath.length;i++){
    const a=Math.min(highlightPath[i],highlightPath[i+1]);
    const b=Math.max(highlightPath[i],highlightPath[i+1]);
    pathSet.add(a+'-'+b);
  }

  // Draw edges
  EDGES_RAW.forEach(([u,v,d,t,toll])=>{
    const p1=nodePos(u), p2=nodePos(v);
    const key=Math.min(u,v)+'-'+Math.max(u,v);
    const onPath=pathSet.has(key);
    c.beginPath();
    c.moveTo(p1.x,p1.y);
    c.lineTo(p2.x,p2.y);
    if(onPath){
      c.strokeStyle='#00e5a0';
      c.lineWidth=3;
      c.shadowColor='#00e5a0';
      c.shadowBlur=12;
    } else {
      c.strokeStyle='rgba(255,255,255,0.1)';
      c.lineWidth=1.5;
      c.shadowBlur=0;
    }
    c.stroke();
    c.shadowBlur=0;

    // Edge label
    const mx=(p1.x+p2.x)/2, my=(p1.y+p2.y)/2;
    const w = currentMode===0?d:currentMode===1?t:toll;
    const unit = currentMode===0?'km':currentMode===1?'m':'₹';
    c.fillStyle=onPath?'#00e5a0':'rgba(255,255,255,0.25)';
    c.font=`${onPath?'600':'400'} 10px JetBrains Mono,monospace`;
    c.textAlign='center';
    c.fillText(w+unit, mx, my-8);
  });

  // Draw nodes
  const src = parseInt(document.getElementById('srcSel').value||0);
  const dst = parseInt(document.getElementById('dstSel').value||4);

  CITIES.forEach((name,i)=>{
    const {x,y}=nodePos(i);
    const onPath = highlightPath.includes(i);
    const isSrc = i===src, isDst = i===dst;

    // Outer ring
    if(onPath||isSrc||isDst){
      c.beginPath();
      c.arc(x,y,28,0,Math.PI*2);
      c.strokeStyle = isSrc?'#ffd700': isDst?'#ff6b35':'#00e5a0';
      c.lineWidth=2;
      c.globalAlpha=0.3;
      c.stroke();
      c.globalAlpha=1;
    }

    // Node circle
    c.beginPath();
    c.arc(x,y,20,0,Math.PI*2);
    let fill = '#151b24';
    if(isSrc) fill='rgba(255,215,0,0.15)';
    else if(isDst) fill='rgba(255,107,53,0.15)';
    else if(onPath) fill='rgba(0,229,160,0.12)';
    c.fillStyle=fill;
    c.fill();
    c.strokeStyle = isSrc?'#ffd700':isDst?'#ff6b35':onPath?'#00e5a0':'rgba(255,255,255,0.2)';
    c.lineWidth=isSrc||isDst?2:1.5;
    if(onPath&&!isSrc&&!isDst){c.shadowColor='#00e5a0';c.shadowBlur=10}
    c.stroke();
    c.shadowBlur=0;

    // Index
    c.fillStyle = isSrc?'#ffd700':isDst?'#ff6b35':onPath?'#00e5a0':'rgba(255,255,255,0.5)';
    c.font='600 11px JetBrains Mono,monospace';
    c.textAlign='center';
    c.textBaseline='middle';
    c.fillText(i,x,y);

    // Name
    c.fillStyle = onPath||isSrc||isDst?'#e8edf4':'rgba(255,255,255,0.4)';
    c.font=`${onPath||isSrc||isDst?'600':'400'} 11px Syne,sans-serif`;
    c.textBaseline='top';
    c.fillText(name,x,y+26);
  });
}

// ── ALGORITHM IMPLEMENTATIONS ──────────────────
function dijkstra(src,dst,mode){
  const dist=Array(N).fill(Infinity), par=Array(N).fill(-1), vis=Array(N).fill(false);
  dist[src]=0;
  const pq=[[0,src]];
  while(pq.length){
    pq.sort((a,b)=>a[0]-b[0]);
    const [d,u]=pq.shift();
    if(vis[u])continue;
    vis[u]=true;
    for(const e of ADJ[u]){
      const w=mode===0?e.dist:mode===1?e.time:e.toll;
      if(dist[u]+w<dist[e.to]){dist[e.to]=dist[u]+w;par[e.to]=u;pq.push([dist[e.to],e.to])}
    }
  }
  if(dist[dst]===Infinity)return null;
  const path=[];for(let v=dst;v!==-1;v=par[v])path.push(v);path.reverse();
  return {path,cost:dist[dst]};
}

function bfs(src,dst){
  const vis=Array(N).fill(false),par=Array(N).fill(-1),q=[src];
  vis[src]=true;
  while(q.length){const u=q.shift();if(u===dst)break;for(const e of ADJ[u])if(!vis[e.to]){vis[e.to]=true;par[e.to]=u;q.push(e.to)}}
  if(!vis[dst])return null;
  const path=[];for(let v=dst;v!==-1;v=par[v])path.push(v);path.reverse();
  return {path,stops:path.length-1};
}

function dfsAll(src,dst){
  const all=[];
  function dfs(u,vis,path){
    vis[u]=true;path.push(u);
    if(u===dst)all.push([...path]);
    else for(const e of ADJ[u])if(!vis[e.to])dfs(e.to,vis,path);
    path.pop();vis[u]=false;
  }
  dfs(src,Array(N).fill(false),[]);
  return all;
}

function pathMetrics(path){
  let d=0,t=0,tl=0;
  for(let i=0;i+1<path.length;i++){
    for(const e of ADJ[path[i]])if(e.to===path[i+1]){d+=e.dist;t+=e.time;tl+=e.toll;break}
  }
  return {d,t,tl};
}

let currentAlgoMode=0;
function setMode(m,btn){
  currentAlgoMode=m;
  document.querySelectorAll('.algo-tab').forEach(b=>b.classList.remove('active'));
  if(btn)btn.classList.add('active');
  ['mb0','mb1','mb2'].forEach((id,i)=>document.getElementById(id).classList.toggle('active',i===m&&m<3));
  currentMode=Math.min(m,2);
  drawGraph(currentPath);
}

function runAlgo(){
  const src=parseInt(document.getElementById('srcSel').value);
  const dst=parseInt(document.getElementById('dstSel').value);
  const card=document.getElementById('resultCard');

  if(src===dst){card.innerHTML='<div style="color:var(--muted);font-size:12px;font-family:var(--mono)">Source and destination are the same.</div>';return}

  let result=null;

  if(currentAlgoMode<=2){
    result=dijkstra(src,dst,currentAlgoMode);
    if(!result){card.innerHTML='<div style="color:var(--accent3);font-size:12px;font-family:var(--mono)">No path found.</div>';return}
    const {d,t,tl}=pathMetrics(result.path);
    const labels=['Distance','Time','Toll'],units=['km','min','₹'];
    card.innerHTML=`
      <div class="panel-label" style="margin-bottom:10px">RESULT — DIJKSTRA (${labels[currentAlgoMode].toUpperCase()})</div>
      <div class="res-metric"><span class="res-key">Optimal ${labels[currentAlgoMode]}</span><span class="res-val">${result.cost} ${units[currentAlgoMode]}</span></div>
      <div class="res-metric"><span class="res-key">Distance</span><span class="res-val">${d} km</span></div>
      <div class="res-metric"><span class="res-key">Travel Time</span><span class="res-val">${t} min</span></div>
      <div class="res-metric"><span class="res-key">Total Toll</span><span class="res-val">₹${tl}</span></div>
      <div class="res-metric"><span class="res-key">Stops</span><span class="res-val">${result.path.length-1}</span></div>
      <div class="panel-label" style="margin:12px 0 8px">PATH</div>
      <div class="path-chips">${result.path.map((n,i)=>`${i>0?'<span class="arrow-chip">→</span>':''}<span class="path-chip ${n===src?'src-chip':n===dst?'dst-chip':''}">${n}:${CITIES[n]}</span>`).join('')}</div>`;
    currentPath=result.path;
  } else if(currentAlgoMode===3){
    const r=bfs(src,dst);
    if(!r){card.innerHTML='<div style="color:var(--accent3);font-size:12px;font-family:var(--mono)">No path found.</div>';return}
    const {d,t,tl}=pathMetrics(r.path);
    card.innerHTML=`
      <div class="panel-label" style="margin-bottom:10px">RESULT — BFS (FEWEST STOPS)</div>
      <div class="res-metric"><span class="res-key">Stops</span><span class="res-val">${r.stops}</span></div>
      <div class="res-metric"><span class="res-key">Distance</span><span class="res-val">${d} km</span></div>
      <div class="res-metric"><span class="res-key">Travel Time</span><span class="res-val">${t} min</span></div>
      <div class="res-metric"><span class="res-key">Total Toll</span><span class="res-val">₹${tl}</span></div>
      <div class="panel-label" style="margin:12px 0 8px">PATH</div>
      <div class="path-chips">${r.path.map((n,i)=>`${i>0?'<span class="arrow-chip">→</span>':''}<span class="path-chip ${n===src?'src-chip':n===dst?'dst-chip':''}">${n}:${CITIES[n]}</span>`).join('')}</div>`;
    currentPath=r.path;
  } else {
    const all=dfsAll(src,dst);
    const sorted=[...all].sort((a,b)=>pathMetrics(a).d-pathMetrics(b).d);
    if(all.length===0){card.innerHTML='<div style="color:var(--accent3);font-size:12px;font-family:var(--mono)">No routes found.</div>';return}
    let html=`<div class="panel-label" style="margin-bottom:10px">ALL ROUTES — DFS (${all.length} found)</div>`;
    sorted.forEach((path,i)=>{
      const {d,t,tl}=pathMetrics(path);
      html+=`<div style="padding:8px 0;border-bottom:1px solid var(--border);font-size:11px;font-family:var(--mono)">
        <div style="color:var(--muted);margin-bottom:4px">#${i+1} · ${d}km / ${t}min / ₹${tl}</div>
        <div style="color:var(--muted2)">${path.map(n=>CITIES[n]).join(' → ')}</div>
      </div>`;
    });
    card.innerHTML=html;
    currentPath=sorted[0];
  }
  drawGraph(currentPath);
}

// ── SELECTS ───────────────────────────────────
function initSelects(){
  const src=document.getElementById('srcSel');
  const dst=document.getElementById('dstSel');
  CITIES.forEach((c,i)=>{
    src.innerHTML+=`<option value="${i}">${i} – ${c}</option>`;
    dst.innerHTML+=`<option value="${i}" ${i===4?'selected':''}>${i} – ${c}</option>`;
  });
  src.addEventListener('change',()=>drawGraph(currentPath));
  dst.addEventListener('change',()=>drawGraph(currentPath));
}

// ── BLOOM FILTER ───────────────────────────────
const REGISTERED = ['DL01AB1234','UP14CD5678','HR26EF9012','UK07GH3456','DL02IJ7890','UP80KL2345'];
const BITS=1024;
const bloom=new Uint8Array(BITS);

function h1(s){let h=0;for(let c of s)h=(h*31+c.charCodeAt(0))%BITS;return h}
function h2(s){let h=0;for(let c of s)h=(h*37+c.charCodeAt(0))%BITS;return h}
function h3(s){let h=5381;for(let c of s)h=((h<<5)+h)^c.charCodeAt(0);return Math.abs(h)%BITS}

function bfInsert(s){bloom[h1(s)]=1;bloom[h2(s)]=1;bloom[h3(s)]=1}
function bfCheck(s){return bloom[h1(s)]&&bloom[h2(s)]&&bloom[h3(s)]}

function initBloom(){
  REGISTERED.forEach(v=>bfInsert(v));
  const list=document.getElementById('regList');
  REGISTERED.forEach(v=>{
    const el=document.createElement('div');
    el.className='v-tag'; el.textContent=v;
    el.onclick=()=>{document.getElementById('vInput').value=v;checkVehicle()};
    list.appendChild(el);
  });
}

function checkVehicle(){
  const v=document.getElementById('vInput').value.trim().toUpperCase();
  const r=document.getElementById('bloomResult');
  if(!v){r.className='bloom-result';return}
  const passed=bfCheck(v);
  r.className='bloom-result show '+(passed?'yes':'no');
  r.textContent=passed
    ?`✓ ${v} — Likely passed toll (Bloom says YES)`
    :`✗ ${v} — Has NOT passed toll (Bloom says NO)`;
}

// ── FENWICK TREE ───────────────────────────────
const TOLL_DATA = [0,12500,9800,15200,11000];
const fenwick=new Array(N+1).fill(0);
TOLL_DATA.forEach((v,i)=>{
  for(let j=i+1;j<=N;j+=j&(-j))fenwick[j]+=v;
});

function fenwickQuery(i){let s=0;for(let j=i+1;j>0;j-=j&(-j))s+=fenwick[j];return s}
function fenwickRange(l,r){return fenwickQuery(r)-(l>0?fenwickQuery(l-1):0)}

function initFenwick(){
  const bars=document.getElementById('fBars');
  const max=Math.max(...TOLL_DATA.slice(1));
  TOLL_DATA.forEach((v,i)=>{
    if(i===0)return; // skip Delhi (no toll)
    const wrap=document.createElement('div');wrap.className='f-bar-wrap';
    const bar=document.createElement('div');bar.className='f-bar';
    const pct=(v/max)*100;
    bar.style.height=pct+'%';
    bar.style.background=`linear-gradient(to top,#00e5a0,#0098ff)`;
    const lbl=document.createElement('div');lbl.className='f-label';lbl.textContent=CITIES[i];
    const val=document.createElement('div');val.className='f-val';val.textContent='₹'+v.toLocaleString();
    wrap.appendChild(val);wrap.appendChild(bar);wrap.appendChild(lbl);
    bars.appendChild(wrap);
  });
  document.getElementById('qR').max=N-1;
  document.getElementById('qL').max=N-1;
}

function fenwickQueryBtn(){
  const l=parseInt(document.getElementById('qL').value)||0;
  const r=parseInt(document.getElementById('qR').value)||N-1;
  const res=fenwickRange(Math.max(0,l),Math.min(N-1,r));
  document.getElementById('qResult').textContent='= ₹'+res.toLocaleString();
}
document.addEventListener('DOMContentLoaded',()=>{
  document.querySelector('.q-btn').onclick=fenwickQueryBtn;
});

// ── KRUSKAL MST ───────────────────────────────
function kruskalMST(){
  const allEdges=[...EDGES_RAW].sort((a,b)=>a[2]-b[2]);
  const parent=Array.from({length:N},(_,i)=>i);
  function find(x){return parent[x]===x?x:parent[x]=find(parent[x])}
  function unite(x,y){x=find(x);y=find(y);if(x===y)return false;parent[y]=x;return true}

  const mst=new Set();
  let total=0;
  for(const [u,v,d] of allEdges){
    if(unite(u,v)){mst.add(Math.min(u,v)+'-'+Math.max(u,v));total+=d}
  }

  document.getElementById('mstTotal').textContent=total;

  // Edge list
  const list=document.getElementById('mstEdgeList');
  allEdges.forEach(([u,v,d])=>{
    const key=Math.min(u,v)+'-'+Math.max(u,v);
    const inMST=mst.has(key);
    const row=document.createElement('div');
    row.className='mst-edge-row'+(inMST?' in-mst':'');
    row.innerHTML=`<span class="edge-cities">${CITIES[u]} ↔ ${CITIES[v]}</span><span class="edge-dist">${d}km</span>${inMST?'<span class="mst-badge">MST</span>':''}`;
    list.appendChild(row);
  });

  // MST Canvas
  const mc=document.getElementById('mstCanvas');
  const mctx=mc.getContext('2d');
  mc.width=mc.parentElement.offsetWidth||400;
  mc.height=260;
  const W=mc.width, H=mc.height;
  const pos=POSITIONS.map(p=>({x:p.x*W,y:p.y*H}));

  mctx.clearRect(0,0,W,H);
  mctx.strokeStyle='rgba(255,255,255,0.06)';mctx.lineWidth=1;
  for(let x=0;x<W;x+=30){mctx.beginPath();mctx.moveTo(x,0);mctx.lineTo(x,H);mctx.stroke()}
  for(let y=0;y<H;y+=30){mctx.beginPath();mctx.moveTo(0,y);mctx.lineTo(W,y);mctx.stroke()}

  EDGES_RAW.forEach(([u,v])=>{
    const key=Math.min(u,v)+'-'+Math.max(u,v);
    const inMST=mst.has(key);
    mctx.beginPath();mctx.moveTo(pos[u].x,pos[u].y);mctx.lineTo(pos[v].x,pos[v].y);
    if(inMST){mctx.strokeStyle='#00e5a0';mctx.lineWidth=2.5;mctx.shadowColor='#00e5a0';mctx.shadowBlur=8}
    else{mctx.strokeStyle='rgba(255,255,255,0.1)';mctx.lineWidth=1;mctx.shadowBlur=0}
    mctx.stroke();mctx.shadowBlur=0;
  });
  CITIES.forEach((name,i)=>{
    const {x,y}=pos[i];
    mctx.beginPath();mctx.arc(x,y,14,0,Math.PI*2);
    mctx.fillStyle='#151b24';mctx.fill();
    mctx.strokeStyle='#00e5a0';mctx.lineWidth=1.5;mctx.stroke();
    mctx.fillStyle='#00e5a0';mctx.font='10px JetBrains Mono,monospace';mctx.textAlign='center';mctx.textBaseline='middle';mctx.fillText(i,x,y);
    mctx.fillStyle='rgba(255,255,255,0.5)';mctx.font='9px Syne,sans-serif';mctx.textBaseline='top';mctx.fillText(name,x,y+18);
  });
}

// ── COUNTER ANIMATION ─────────────────────────
function animCount(id,target,suffix=''){
  const el=document.getElementById(id);
  let start=0;
  const step=()=>{start=Math.min(start+Math.ceil(target/40),target);el.textContent=start+(suffix);if(start<target)requestAnimationFrame(step)};
  step();
}

// ── INIT ──────────────────────────────────────
window.addEventListener('load',()=>{
  initSelects();
  resizeCanvas();
  initBloom();
  initFenwick();
  kruskalMST();
  animCount('cnt-nodes',5);
  animCount('cnt-edges',5);
  animCount('cnt-algos',8);
  animCount('cnt-km',192,'');
  drawGraph();

  // Auto-run default
  setTimeout(()=>{runAlgo();},400);
});
window.addEventListener('resize',resizeCanvas);

// expose for onclick
window.checkVehicle=checkVehicle;
window.fenwickQuery=fenwickQueryBtn;
window.setMode=setMode;
window.runAlgo=runAlgo;
</script>
</body>
</html>
