const server = Bun.serve({
  port: 0,
  async fetch(req: Request) {
    if (req.url.endsWith("/gc")) {
      Bun.gc(true);
      return new Response("Ok");
    }
    if (req.url.endsWith("/report")) {
      Bun.gc(true);
      return new Response(JSON.stringify(process.memoryUsage.rss()), {
        headers: {
          "Content-Type": "application/json",
        },
      });
    }
    if (req.url.endsWith("/buffering")) {
      await req.text();
    } else if (req.url.endsWith("/streaming")) {
      const reader = req.body?.getReader();
      while (true) {
        const { done, value } = await reader?.read();
        if (done) {
          break;
        }
      }
    } else if (req.url.endsWith("/incomplete-streaming")) {
      const reader = req.body?.getReader();
      await reader?.read();
    }
    return new Response("Ok");
  },
});
console.log(server.url.href);
