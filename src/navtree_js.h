"\n"
"var navTreeIndex;\n"
"\n"
"function getData(varName)\n"
"{\n"
"  var i = varName.lastIndexOf('/');\n"
"  var n = i>=0 ? varName.substring(i+1) : varName;\n"
"  return eval(n);\n"
"}\n"
"\n"
"function stripPath(uri)\n"
"{\n"
"  return uri.substring(uri.lastIndexOf('/')+1);\n"
"}\n"
"\n"
"function getScript(scriptName,func,show)\n"
"{\n"
"  var head = document.getElementsByTagName(\"head\")[0]; \n"
"  var script = document.createElement('script');\n"
"  script.id = scriptName;\n"
"  script.type = 'text/javascript';\n"
"  script.onload = func; \n"
"  script.src = scriptName+'.js'; \n"
"  if ($.browser.msie && $.browser.version<=8) { \n"
"    // script.onload does work with older versions of IE\n"
"    script.onreadystatechange = function() {\n"
"      if (script.readyState=='complete' || script.readyState=='loaded') { \n"
"        func(); if (show) showRoot(); \n"
"      }\n"
"    }\n"
"  }\n"
"  head.appendChild(script); \n"
"}\n"
"\n"
"function createIndent(o,domNode,node,level)\n"
"{\n"
"  if (node.parentNode && node.parentNode.parentNode) {\n"
"    createIndent(o,domNode,node.parentNode,level+1);\n"
"  }\n"
"  var imgNode = document.createElement(\"img\");\n"
"  imgNode.width = 16;\n"
"  imgNode.height = 22;\n"
"  if (level==0 && node.childrenData) {\n"
"    node.plus_img = imgNode;\n"
"    node.expandToggle = document.createElement(\"a\");\n"
"    node.expandToggle.href = \"javascript:void(0)\";\n"
"    node.expandToggle.onclick = function() {\n"
"      if (node.expanded) {\n"
"        $(node.getChildrenUL()).slideUp(\"fast\");\n"
"        if (node.isLast) {\n"
"          node.plus_img.src = node.relpath+\"ftv2plastnode.png\";\n"
"        } else {\n"
"          node.plus_img.src = node.relpath+\"ftv2pnode.png\";\n"
"        }\n"
"        node.expanded = false;\n"
"      } else {\n"
"        expandNode(o, node, false, false);\n"
"      }\n"
"    }\n"
"    node.expandToggle.appendChild(imgNode);\n"
"    domNode.appendChild(node.expandToggle);\n"
"  } else {\n"
"    domNode.appendChild(imgNode);\n"
"  }\n"
"  if (level==0) {\n"
"    if (node.isLast) {\n"
"      if (node.childrenData) {\n"
"        imgNode.src = node.relpath+\"ftv2plastnode.png\";\n"
"      } else {\n"
"        imgNode.src = node.relpath+\"ftv2lastnode.png\";\n"
"        domNode.appendChild(imgNode);\n"
"      }\n"
"    } else {\n"
"      if (node.childrenData) {\n"
"        imgNode.src = node.relpath+\"ftv2pnode.png\";\n"
"      } else {\n"
"        imgNode.src = node.relpath+\"ftv2node.png\";\n"
"        domNode.appendChild(imgNode);\n"
"      }\n"
"    }\n"
"  } else {\n"
"    if (node.isLast) {\n"
"      imgNode.src = node.relpath+\"ftv2blank.png\";\n"
"    } else {\n"
"      imgNode.src = node.relpath+\"ftv2vertline.png\";\n"
"    }\n"
"  }\n"
"  imgNode.border = \"0\";\n"
"}\n"
"\n"
"function newNode(o, po, text, link, childrenData, lastNode)\n"
"{\n"
"  var node = new Object();\n"
"  node.children = Array();\n"
"  node.childrenData = childrenData;\n"
"  node.depth = po.depth + 1;\n"
"  node.relpath = po.relpath;\n"
"  node.isLast = lastNode;\n"
"\n"
"  node.li = document.createElement(\"li\");\n"
"  po.getChildrenUL().appendChild(node.li);\n"
"  node.parentNode = po;\n"
"\n"
"  node.itemDiv = document.createElement(\"div\");\n"
"  node.itemDiv.className = \"item\";\n"
"\n"
"  node.labelSpan = document.createElement(\"span\");\n"
"  node.labelSpan.className = \"label\";\n"
"\n"
"  createIndent(o,node.itemDiv,node,0);\n"
"  node.itemDiv.appendChild(node.labelSpan);\n"
"  node.li.appendChild(node.itemDiv);\n"
"\n"
"  var a = document.createElement(\"a\");\n"
"  node.labelSpan.appendChild(a);\n"
"  node.label = document.createTextNode(text);\n"
"  node.expanded = false;\n"
"  a.appendChild(node.label);\n"
"  if (link) {\n"
"    var url;\n"
"    if (link.substring(0,1)=='^') {\n"
"      url = link.substring(1);\n"
"      link = url;\n"
"    } else {\n"
"      url = node.relpath+link;\n"
"    }\n"
"    a.className = stripPath(link.replace('#',':'));\n"
"    if (link.indexOf('#')!=-1) {\n"
"      var aname = '#'+link.split('#')[1];\n"
"      var srcPage = stripPath($(location).attr('pathname'));\n"
"      var targetPage = stripPath(link.split('#')[0]);\n"
"      a.href = srcPage!=targetPage ? url : '#';\n"
"      a.onclick = function(){\n"
"        if (!$(a).parent().parent().hasClass('selected'))\n"
"        {\n"
"          $('.item').removeClass('selected');\n"
"          $('.item').removeAttr('id');\n"
"          $(a).parent().parent().addClass('selected');\n"
"          $(a).parent().parent().attr('id','selected');\n"
"        }\n"
"        var pos, anchor = $(aname), docContent = $('#doc-content');\n"
"        if (anchor.parent().attr('class')=='memItemLeft') {\n"
"          pos = anchor.parent().position().top;\n"
"        } else if (anchor.position()) {\n"
"          pos = anchor.position().top;\n"
"        }\n"
"        if (pos) {\n"
"          var dist = Math.abs(Math.min(\n"
"                     pos-docContent.offset().top,\n"
"                     docContent[0].scrollHeight-\n"
"                     docContent.height()-docContent.scrollTop()));\n"
"          docContent.animate({\n"
"            scrollTop: pos + docContent.scrollTop() - docContent.offset().top\n"
"          },Math.max(50,Math.min(500,dist)),function(){\n"
"            window.location.replace(aname);\n"
"          });\n"
"        }\n"
"      };\n"
"    } else {\n"
"      a.href = url;\n"
"    }\n"
"  } else {\n"
"    if (childrenData != null) \n"
"    {\n"
"      a.className = \"nolink\";\n"
"      a.href = \"javascript:void(0)\";\n"
"      a.onclick = node.expandToggle.onclick;\n"
"    }\n"
"  }\n"
"\n"
"  node.childrenUL = null;\n"
"  node.getChildrenUL = function() {\n"
"    if (!node.childrenUL) {\n"
"      node.childrenUL = document.createElement(\"ul\");\n"
"      node.childrenUL.className = \"children_ul\";\n"
"      node.childrenUL.style.display = \"none\";\n"
"      node.li.appendChild(node.childrenUL);\n"
"    }\n"
"    return node.childrenUL;\n"
"  };\n"
"\n"
"  return node;\n"
"}\n"
"\n"
"function showRoot()\n"
"{\n"
"  var headerHeight = $(\"#top\").height();\n"
"  var footerHeight = $(\"#nav-path\").height();\n"
"  var windowHeight = $(window).height() - headerHeight - footerHeight;\n"
"  (function (){ // retry until we can scroll to the selected item\n"
"    try {\n"
"      var navtree=$('#nav-tree');\n"
"      navtree.scrollTo('#selected',0,{offset:-windowHeight/2});\n"
"    } catch (err) {\n"
"      setTimeout(arguments.callee, 0);\n"
"    }\n"
"  })();\n"
"}\n"
"\n"
"function expandNode(o, node, imm, showRoot)\n"
"{\n"
"  if (node.childrenData && !node.expanded) {\n"
"    if (typeof(node.childrenData)==='string') {\n"
"      var varName    = node.childrenData;\n"
"      getScript(node.relpath+varName,function(){\n"
"        node.childrenData = getData(varName);\n"
"        expandNode(o, node, imm, showRoot);\n"
"      }, showRoot);\n"
"    } else {\n"
"      if (!node.childrenVisited) {\n"
"        getNode(o, node);\n"
"      } if (imm || ($.browser.msie && $.browser.version>8)) { \n"
"        // somehow slideDown jumps to the start of tree for IE9 :-(\n"
"        $(node.getChildrenUL()).show();\n"
"      } else {\n"
"        $(node.getChildrenUL()).slideDown(\"fast\");\n"
"      }\n"
"      if (node.isLast) {\n"
"        node.plus_img.src = node.relpath+\"ftv2mlastnode.png\";\n"
"      } else {\n"
"        node.plus_img.src = node.relpath+\"ftv2mnode.png\";\n"
"      }\n"
"      node.expanded = true;\n"
"    }\n"
"  }\n"
"}\n"
"\n"
"function glowEffect(n,duration)\n"
"{\n"
"  n.addClass('glow').delay(duration).queue(function(next){\n"
"    $(this).removeClass('glow');next();\n"
"  });\n"
"}\n"
"\n"
"function highlightAnchor()\n"
"{\n"
"  var anchor = $($(location).attr('hash'));\n"
"  if (anchor.parent().attr('class')=='memItemLeft'){\n"
"    var rows = $('.memberdecls tr[class$=\"'+\n"
"               window.location.hash.substring(1)+'\"]');\n"
"    glowEffect(rows.children(),300);\n"
"  } else if (anchor.parent().is(\":header\")) {\n"
"    glowEffect(anchor.parent(),1000);\n"
"  } else {\n"
"    glowEffect(anchor.next(),1000);\n"
"  }\n"
"}\n"
"\n"
"function selectAndHighlight(n)\n"
"{\n"
"  var a;\n"
"  if ($(location).attr('hash')) {\n"
"    var link=stripPath($(location).attr('pathname'))+':'+\n"
"      $(location).attr('hash').substring(1);\n"
"    a=$('.item a[class$=\"'+link+'\"]');\n"
"  }\n"
"  if (a && a.length) {\n"
"    a.parent().parent().addClass('selected');\n"
"    a.parent().parent().attr('id','selected');\n"
"    highlightAnchor();\n"
"  } else if (n) {\n"
"    $(n.itemDiv).addClass('selected');\n"
"    $(n.itemDiv).attr('id','selected');\n"
"  }\n"
"  showRoot();\n"
"}\n"
"\n"
"function showNode(o, node, index)\n"
"{\n"
"  if (node && node.childrenData) {\n"
"    if (typeof(node.childrenData)==='string') {\n"
"      var varName    = node.childrenData;\n"
"      getScript(node.relpath+varName,function(){\n"
"        node.childrenData = getData(varName);\n"
"        showNode(o,node,index);\n"
"      },true);\n"
"    } else {\n"
"      if (!node.childrenVisited) {\n"
"        getNode(o, node);\n"
"      }\n"
"      $(node.getChildrenUL()).show();\n"
"      if (node.isLast) {\n"
"        node.plus_img.src = node.relpath+\"ftv2mlastnode.png\";\n"
"      } else {\n"
"        node.plus_img.src = node.relpath+\"ftv2mnode.png\";\n"
"      }\n"
"      node.expanded = true;\n"
"      var n = node.children[o.breadcrumbs[index]];\n"
"      if (index+1<o.breadcrumbs.length) {\n"
"        showNode(o,n,index+1);\n"
"      } else {\n"
"        if (typeof(n.childrenData)==='string') {\n"
"          var varName = n.childrenData;\n"
"          getScript(n.relpath+varName,function(){\n"
"            n.childrenData = getData(varName);\n"
"            node.expanded=false;\n"
"            showNode(o,node,index); // retry with child node expanded\n"
"          },true);\n"
"        } else {\n"
"          if (o.toroot==\"index.html\" || n.childrenData) {\n"
"            expandNode(o, n, true, true);\n"
"          }\n"
"          selectAndHighlight(n);\n"
"        }\n"
"      }\n"
"    }\n"
"  } else {\n"
"    selectAndHighlight();\n"
"  }\n"
"}\n"
"\n"
"function getNode(o, po)\n"
"{\n"
"  po.childrenVisited = true;\n"
"  var l = po.childrenData.length-1;\n"
"  for (var i in po.childrenData) {\n"
"    var nodeData = po.childrenData[i];\n"
"    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],\n"
"      i==l);\n"
"  }\n"
"}\n"
"\n"
"function gotoNode(o,root,hash)\n"
"{\n"
"  var nti = navTreeIndex[root+hash];\n"
"  o.breadcrumbs = nti ? nti : navTreeIndex[root];\n"
"  if (o.breadcrumbs==null) o.breadcrumbs = navTreeIndex[\"index.html\"];\n"
"  o.breadcrumbs.unshift(0);\n"
"  showNode(o, o.node, 0);\n"
"}\n"
"\n"
"function navTo(o,root,hash,relpath)\n"
"{\n"
"  if (navTreeIndex){\n"
"    gotoNode(o,root,hash);\n"
"  } else {\n"
"    getScript(relpath+\"navtreeindex\",function(){\n"
"      navTreeIndex = eval('NAVTREEINDEX');\n"
"      if (navTreeIndex){\n"
"        gotoNode(o,root,hash);\n"
"      }\n"
"    },true);\n"
"  } \n"
"}\n"
"\n"
"function initNavTree(toroot,relpath)\n"
"{\n"
"  var o = new Object();\n"
"  o.toroot = toroot;\n"
"  o.node = new Object();\n"
"  o.node.li = document.getElementById(\"nav-tree-contents\");\n"
"  o.node.childrenData = NAVTREE;\n"
"  o.node.children = new Array();\n"
"  o.node.childrenUL = document.createElement(\"ul\");\n"
"  o.node.getChildrenUL = function() { return o.node.childrenUL; };\n"
"  o.node.li.appendChild(o.node.childrenUL);\n"
"  o.node.depth = 0;\n"
"  o.node.relpath = relpath;\n"
"  o.node.expanded = false;\n"
"  o.node.isLast = true;\n"
"  o.node.plus_img = document.createElement(\"img\");\n"
"  o.node.plus_img.src = relpath+\"ftv2pnode.png\";\n"
"  o.node.plus_img.width = 16;\n"
"  o.node.plus_img.height = 22;\n"
"\n"
"  navTo(o,toroot,window.location.hash,relpath);\n"
"\n"
"  $(window).bind('hashchange', function(){\n"
"     if (window.location.hash && window.location.hash.length>1){\n"
"       var a;\n"
"       if ($(location).attr('hash')){\n"
"         var clslink=stripPath($(location).attr('pathname'))+':'+\n"
"                               $(location).attr('hash').substring(1);\n"
"         a=$('.item a[class$=\"'+clslink+'\"]');\n"
"       }\n"
"       if (a==null || !$(a).parent().parent().hasClass('selected')){\n"
"         $('.item').removeClass('selected');\n"
"         $('.item').removeAttr('id');\n"
"       }\n"
"       var link=stripPath($(location).attr('pathname'));\n"
"       navTo(o,link,$(location).attr('hash'),relpath);\n"
"     }\n"
"  })\n"
"\n"
"  $(window).load(showRoot);\n"
"}\n"
"\n"
