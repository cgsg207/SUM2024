// const requestListener = (req, res) => {
//   res.setHeader("Content-Type", "text/html");
//   res.writeHead(200);
//   res.end(`<html><body><h1>HTML response</h1><body></html>`);
// };

// const requestListener = async (req, res) => {
//   const contents = await fs.readFile(process.cwd() + "/index.html");
//   res.setHeader("Content-Type", "text/html");
//   res.writeHead(200);
//   res.end(contents);
// };

// const requestListener = async (req, res) => {
//     if (req.url == "/") {
//         const contents = await fs.readFile(
//             process.cwd() + "/client/index.html",
//         );
//         res.setHeader("Content-Type", "text/html");
//         res.writeHead(200);
//         res.end(contents);
//     } else {
//         if (req.url.endsWith(".js")) {
//             const contents = await fs.readFile(
//                 process.cwd() + "/client" + req.url,
//             );
//             res.setHeader("Content-Type", "text/javascript");
//             res.writeHead(200);
//             res.end(contents);
//         }
//     }
// };
