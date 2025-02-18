export const activateScrollBar = () => {
  if (
    window.innerWidth > document.body.scrollWidth ||
    window.innerHeight > document.body.scrollHeight
  ) {
    document.body.style.overflow = "auto";
  } else {
    document.body.style.overflow = "hidden";
  }
};
